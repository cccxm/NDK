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
// Created by 陈小默 on 16/11/10.
//

#ifndef NDK_LANG_H
#define NDK_LANG_H
typedef char byte;
typedef unsigned char ubyte;

class Byte {
private:
    byte _byte;
public:
    Byte(byte b) : _byte(b) { }

    int toInt() { return int(_byte); }

    operator byte &() { return _byte; }
};

class UByte {
private:
    ubyte _ubyte;
public:
    UByte(ubyte b) : _ubyte(b) { }

    int toInt() { return int(_ubyte); }

    operator ubyte &() { return _ubyte; }
};


class ByteArray {
private:
    byte *_array;
    int _length;
public:
    ByteArray(int length, byte def = 0);

    ByteArray(int length, byte *arr);

    ~ByteArray();

    int size() { return _length; }

    operator byte *() const { return _array; }
};


class UByteArray {
private:
    ubyte *_array;
    int _length;
public:
    UByteArray(int length, ubyte def = 0);

    ~UByteArray();

    int size() { return _length; }

    operator ubyte *() const { return _array; }

    char *toCharArray() { return (char *) _array; }
};

#endif //NDK_LANG_H
