#include <sstream>
#include <fstream>

#include "texteditor.h"
#include "osk.h"
#include "system_mgr.h"

enum{
    OPT_EDIT,
    OPT_COPY,
    OPT_REMV,
};

static char* EDIT = "          Edit";
static char* COPY = "          Copy";
static char* REMV = "          Remove";
static char* SAVE = "          Saving";
static char* EXIT = "          Not Saving";

TextEditor::TextEditor(string path){
    this->path = path;
    this->clipboard = "<new line>";
    this->table.settings_entries = NULL;
    this->table.max_options = 0;

    this->loadTextFile();

    this->menu = new SettingsMenu(&(this->table), NULL, false, false, false);
}

TextEditor::~TextEditor(){
    
    for (int i=1; i<table.max_options; i++){
        this->removeLine(i);
    }

    text_line_t* tline = (text_line_t*)(table.settings_entries[0]);
    free(tline->description);
    free(tline);

    delete this->menu;
}

void TextEditor::loadTextFile(){
    std::ifstream input(this->path.c_str());

    this->addLine(string("<EXIT>"), SAVE, EXIT, NULL);

    for( std::string line; getline( input, line ); ){
        this->addLine(line, EDIT, COPY, REMV);
    }
}

void TextEditor::saveTextFile(){
    std::ofstream output(this->path.c_str());

    for (int i=1; i<table.max_options; i++){
        output << table.settings_entries[i]->description << endl;
    }

    output.close();
}

void TextEditor::addLine(string line, char* opt1, char* opt2, char* opt3){
    text_line_t* tline = (text_line_t*)malloc(sizeof(text_line_t));
    tline->description = strdup(line.c_str());
    tline->max_options = 2;
    tline->selection = 0;
    tline->config_ptr = &(tline->selection);
    tline->options[0] = opt1;
    tline->options[1] = opt2;

    if (opt3){
        tline->options[2] = opt3;
        tline->max_options++;
    }

    if (table.settings_entries == NULL){ // create initial table
        table.settings_entries = (settings_entry**)malloc(8 * sizeof(settings_entry*));
        lines_max = 8;
        table.max_options = 0;
    }
    if (table.max_options >= lines_max){ // resize table
        settings_entry** new_table = (settings_entry**)malloc(2 * lines_max * sizeof(settings_entry*));
        for (int i=0; i<table.max_options; i++) new_table[i] = table.settings_entries[i];
        free(table.settings_entries);
        table.settings_entries = new_table;
        lines_max *= 2;
    }
    table.settings_entries[table.max_options++] = (settings_entry*)tline;
}

void TextEditor::insertLine(int i, string line, char* opt1, char* opt2, char* opt3){
    this->addLine(line, opt1, opt2, opt3);
    text_line_t* tline = (text_line_t*)(table.settings_entries[table.max_options-1]);

    for (int j=table.max_options-1; j>i; j--){
        table.settings_entries[j] = table.settings_entries[j-1];
    }

    table.settings_entries[i] = (settings_entry*)tline;
}

void TextEditor::removeLine(int i){
    if (i == 0) return;

    SystemMgr::pauseDraw();

    text_line_t* tline = (text_line_t*)(table.settings_entries[i]);

    for (int j=i; j<table.max_options-1; j++){
        table.settings_entries[j] = table.settings_entries[j+1];
    }
    table.max_options--;

    free(tline->description);
    free(tline);

    SystemMgr::resumeDraw();
}

void TextEditor::editLine(int i){
    if (i == 0) return;

    text_line_t* tline = (text_line_t*)(table.settings_entries[i]);

    SystemMgr::pauseDraw();
    OSK osk;
    osk.init("Edit Line", tline->description, strlen(tline->description)+50);
    osk.loop();
    int osk_res = osk.getResult();
    if(osk_res != OSK_CANCEL)
    {
        char* tmpText = (char*)malloc(strlen(tline->description)+50);
        osk.getText((char*)tmpText);
        char* oldText = tline->description;
        tline->description = tmpText;
        free(oldText);
    }
    osk.end();
    SystemMgr::resumeDraw();

}

        
void TextEditor::draw(){
    this->menu->draw();
}
        
int TextEditor::control(){

    Controller pad;
    pad.flush();
    
    bool running = true;

    while (running){
        pad.update();

        if (pad.accept()){
            int i = this->menu->getIndex();
            text_line_t* tline = (text_line_t*)(table.settings_entries[i]);
            if (i == 0){
                if (tline->selection == 0){
                    this->saveTextFile();
                }
                running = false;
            }
            else{
                switch(tline->selection){
                    case OPT_EDIT:
                        this->editLine(i);
                        break;
                    case OPT_COPY:
                        this->clipboard = table.settings_entries[i]->description;
                        break;
                    case OPT_REMV:
                        this->removeLine(i);
                        break;
                }
            }
            pad.flush();
        }
        else if (pad.square()){
            int i = this->menu->getIndex();
            this->insertLine(i+1, clipboard, EDIT, COPY, REMV);
            this->editLine(i+1);
            pad.flush();
        }
        else if (pad.decline()){
            running = false;
        }
        else{
            this->menu->control(&pad);
        }
    }

    pad.flush();

    this->menu->pause();

    return 0;

}