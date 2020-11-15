
#ifndef template_h
#define template_h

#include <FS.h>

typedef String (*TemplateCallbackFunction)(const String &key);

class Template : public Printable
{
public:
    Template(fs::FS *fs, const char *filename, TemplateCallbackFunction callback);
    size_t printTo(Print &p) const;
    ~Template();

private:
    fs::FS *_fs;
    char *_filename;
    TemplateCallbackFunction _callback;

    String *_replacement = NULL;
};

#endif
