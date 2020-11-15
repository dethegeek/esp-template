# Abstract

This is a minimal templating engine for ESP32, made to run with ESP32 HTTPS Server (https://github.com/fhessel/esp32_https_server)

It should be able to output on any object implementing Print interface as well.

It is published here after seeing this issue : https://github.com/fhessel/esp32_https_server/issues/25

# Features

- Placeholders
- Template nesting

# Missing Features (may be implemetned if I need them)

- Loops
- Alternatives (might be hard to implement with minimal footprint)

# Templating syntax (case sensitive)

## Placeholders

A placeholder is delimited by a double curly bracket pair. Exemple ```{{PLACEHOLDER}}```. The name between them is the key for a replacement passed to  the callback in charge if solving the placeholder. It is case sensitive and may contain any chararacter excluding closing curly brackets.

## Inclusion

An inclusion is delimited by a pair of double hash. Exemple ```##/menu.html##```. The path between the delimiters is the path to a file read and interpret in the templating system.

# Solver callback

The solver callback is any function receibing a key and outputing a string

```
String templateSolver(const String &key)
{
    if (key.equals("MAC"))
    {
        return WiFi.macAddress();
    }
    else if (key.equals("IP"))
    {
        return WiFi.localIP();
    }
    return "";
}
```

The following function is a callback passed to a ResourceNode object of the HTTPS server
```
void renderIndex(HTTPRequest *req, HTTPResponse *res)
{
    Template tpl = Template(&SPIFFS, "/index.html", &templateSolver);
    // /index.html is found in the SPIFFS, read, interpreted
    // and the result sent to a Print object
    tpl.printTo(*res);
}
```

# template examples
An example of templates

## /index.html

```html
##/header.html##
##/content.html##
<main><h1>Py awesome project</h1></main>
##/footer.html##
```

## /header.html
```html
<!DOCTYPE html>
<html>
<header>
    <title>My awesome project</title>
    <link rel="stylesheet" type="text/css" href="style.css">
</header>
<body>
```

## /content.html
```html
<main>
<p>My IP address is {{IP}}</p>
<p>My MAC address is {{MAC}}</p>
</main>
```

## /footer.html
```html
<footer>DIY Dawn simulator | uptime: {{UPTIME}}</footer>
</body>
</html>
```
