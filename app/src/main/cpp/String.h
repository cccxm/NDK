/**
 *  project:NDK
 *  Copyright (C) <2016>  <陈小默>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
//
// Created by 陈小默 on 16/11/8.
//

#ifndef NDK_STRING_H
#define NDK_STRING_H

class String {
private:
    friend class StringArray;

    friend class StringBuilder;

    char *_str;
    int _size;

    String();

public:

    String(String &str);

    String(char *str);

    ~String();

    operator char *() { return _str; }

    String &operator=(char *str);

    int size() { return _size; }
};

class StringArray {
private:
    String *_arr;
    int _size;
public:
    StringArray(const int len) : _size(len) { _arr = new String[len]; }

    ~StringArray() { delete[] _arr; }

    int size() { return _size; }

    operator String *() { return _arr; }
};


class StringBuilder {
private:
    char *_buffer;
    int _max;
    int _size;
public:
    StringBuilder(String &str);

    StringBuilder(unsigned capacity = 64);

    ~StringBuilder();

    StringBuilder &append(char *str);

    StringBuilder &append(char *arr, unsigned off, unsigned len);

    StringBuilder &append(char c);

    StringBuilder &append(int value, int radix = 10);

    StringBuilder &append(float value);

    int size() { return _size; }

    String &toString();
};

void toString(int value, char *buffer, int radix);

#endif //NDK_STRING_H
