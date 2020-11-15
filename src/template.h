
#ifndef template_h
#define template_h

#include <functional>

#include <FS.h>

typedef std::function<String(const String &key)> TemplateCallbackFunction;

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
