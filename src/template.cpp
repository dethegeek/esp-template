#include "template.h"

size_t Template::printTo(Print& p) const {
    size_t n = 0;
    File file = _fs->open(_filename);
    String placeholderName;
    String includeFilename;
    bool inPlaceholder = false;
    bool inInclude = false;

    while (file.available()) {
        int c = file.read();

        // Check for placeholder boundaries
        if (inPlaceholder == false && inInclude == false && c == '{' && file.peek() == '{') {
            file.read(); // consume 2nd '{'
            placeholderName = "";
            inPlaceholder = true;
            continue;
        }
        if (inPlaceholder == true && inInclude == false && c == '}' && file.peek() == '}') {
            file.read(); // consume 2nd '}'
            inPlaceholder = false;
            String buffer;
            buffer = _callback(placeholderName);
            n += p.print(buffer);
            continue;
        }

        // check for include tag boundaries
        if (inPlaceholder == false && inInclude == false && c == '#' && file.peek() == '#') {
            file.read(); // consume 2nd '#'
            includeFilename = "";
            inInclude = true;
            continue;
        }
        if (inPlaceholder == false && inInclude == true && c == '#' && file.peek() == '#') {
            file.read(); // consume 2nd '#'
            inInclude = false;
            Template inner = Template(_fs, includeFilename.c_str(), _callback);
            n += inner.printTo(p);
            continue;
        }
        if (inPlaceholder) {
            placeholderName.concat((char) c);
        } else if (inInclude) {
            includeFilename.concat((char) c);
        } else {
            p.write((char) c);
            n++;
        }
    }

    file.close();
    return n;
}

Template::Template(fs::FS* fs, const char* filename, TemplateCallbackFunction callback) {
    _fs = fs;
    _filename = (char*) malloc(strlen(filename));
    strcpy(_filename , filename);
    _callback = callback;
}

Template::~Template() {}