#include <Terminal.h>

void Terminal::setup(const char *p)
{
    int len = strlen(p);
    const char *dot = strrchr(p, '.');
    if (dot == NULL)
    {
        dot = p + len - 3;
    }
    // keep prefix short
    strncpy(prefix, dot, sizeof(prefix));
    strncat(prefix, "> ", sizeof(prefix));
    serial.flush();
}

void Terminal::reset()
{
    in_count = 0;
    memset(in, 0, in_size);
}

void Terminal::prompt()
{
    if (prompt_user)
    {
        println("");
        print(prefix);
        prompt_user = false;
    }
}

void Terminal::overflow()
{
    if (overflow_detected)
    {
        reset();
        if (println("overflow"))
        {
            overflow_detected = false;
        }
    }
}

size_t Terminal::print(char c)
{
    size_t res = 0;
    if (serial.availableForWrite())
    {
        res = 1;
        serial.print(c);
        serial.flush();
    }
    return res;
}

size_t Terminal::print(const char *s)
{
    size_t res = 0;
    if (serial.availableForWrite())
    {
        res = 1;
        serial.print(s);
        serial.flush();
    }
    return res;
}

size_t Terminal::println(const char *s)
{
    size_t res = 0;
    if (serial.availableForWrite())
    {
        res = 1;
        serial.println(s);
        serial.flush();
    }
    return res;
}

bool Terminal::ready()
{
    size_t echo_count = in_count;
    int c = -1;
    while (serial.available())
    {
        c = serial.read();
        if (c == -1)
        {
            continue;
        }

        // discard cr
        if (c == 13)
        {
            continue;
        }

        // acknowledge lf
        if (c == 10)
        {
            prompt_user = true;
            if (in_count == 0)
            {
                continue;
            }
            if (!command_ready)
            {
                in[in_count] = 0;
                strncpy(command, in, sizeof(command));
                command_ready = true;
            }
            reset();
            continue;
        }

        in[in_count] = c;
        if (++in_count >= in_size)
        {
            reset();
            overflow_detected = true;
        }
    }

    // do one of these functions per loop cycle
    // even if all 3 are applicable
    if (echo_count < in_count)
    {
        print(in + echo_count);
    }
    else if (overflow_detected)
    {
        overflow();
    }
    else if (prompt_user)
    {
        blink();
        prompt();
    }

    return command_ready;
}

const char *Terminal::get()
{
    if (command_ready)
    {
        command_ready = false;
        return command;
    }
    return NULL;
}
