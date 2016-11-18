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
#include "JniUtil.h"
#include <fstream>

void
toString(int value, char *buffer, int radix) {
    char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned uNum;
    int i = 0, j, k;
    if (radix == 10 && value < 0) {
        uNum = unsigned(-value);
        buffer[i++] = '-';
    } else uNum = unsigned(value);
    do {
        buffer[i++] = index[uNum % (unsigned) radix];
        uNum /= radix;
    } while (uNum);
    buffer[i] = '\0';
    if (buffer[0] == '-') k = 1;
    else k = 0;
    char temp;
    for (j = k; j <= (i - k - 1) / 2.0; j++) {
        temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
}

String::String() : _size(0) {
    _str = (char *) malloc(sizeof(char));
    _str[0] = '\0';
}

String::String(String &str) {
    _size = str._size;
    _str = (char *) malloc(sizeof(char) * _size);
    strcpy(_str, str._str);
}

String::String(char *str) {
    _size = int(strlen(str));
    _str = (char *) malloc(sizeof(char) * _size);
    strcpy(_str, str);
}

String::~String() { free(_str); }

String &
String::operator=(char *str) {
    _size = int(strlen(str));
    _str = (char *) malloc(sizeof(char) * _size);
    strcpy(_str, str);
    return *this;
}

StringBuilder::StringBuilder(String &str) {
    _size = str._size;
    _max = _size + 1;
    _buffer = (char *) malloc(sizeof(char) * _max);
    strcpy(_buffer, str);
}

StringBuilder::StringBuilder(unsigned capacity) {
    _size = capacity;
    _max = _size + 1;
    _buffer = (char *) malloc(sizeof(char) * _max);
    _buffer[0] = '\0';
}

StringBuilder::~StringBuilder() { free(_buffer); }

StringBuilder &
StringBuilder::append(char *str) {
    int nMax = _max;
    auto size = strlen(str);
    while (_size + size >= nMax)nMax *= 2;
    if (nMax != _max) {
        _max = nMax;
        char *nStr = (char *) malloc(sizeof(char) * _max);
        strcpy(nStr, _buffer);
        free(_buffer);
        _buffer = nStr;
    }
    for (int i = 0; _buffer[_size++] = str[i]; i++);
    *(_buffer + _size) = '\0';
    return *this;
}

StringBuilder &
StringBuilder::append(char *arr, unsigned off, unsigned len) {
    char *str = new char[len + 1];
    auto size = strlen(arr);
    if (size < off + len) return *this;
    arr = arr + off;
    memcpy(str, arr, len);
    StringBuilder &temp = append(str);
    delete[] str;
    return temp;
}

StringBuilder &
StringBuilder::append(char c) {
    if (_size == _max - 1) {
        _max *= 2;
        realloc(_buffer, _max);
    }
    _buffer[_size++] = c;
    _buffer[_size] = '\0';
    return *this;
}

StringBuilder &
StringBuilder::append(int value, int radix) {
    char buffer[22];
    ::toString(value, buffer, radix);
    return append(buffer);
}

StringBuilder
&StringBuilder::append(float value) {
    char buffer[32];
    sprintf(buffer, "%f", value);
    return append(buffer);
}

String &
StringBuilder::toString() {
    return *(new String(_buffer));
}

ByteArray::ByteArray(int length, byte def) : _length(length) {
    _array = (byte *) malloc(sizeof(byte) * length);
    for (int i = 0; i < length; _array[i++] = def);
}

ByteArray::ByteArray(int length, byte *arr) {
    _length = length;
    _array = (byte *) malloc(sizeof(byte) * length);
    for (int i = 0; i < length; _array[i] = arr[i], i++);
}

ByteArray::~ByteArray() { free(_array); }

UByteArray::UByteArray(int length, ubyte def) : _length(length) {
    _array = (ubyte *) malloc(sizeof(ubyte) * length);
    for (int i = 0; i < length; _array[i++] = def);
}

UByteArray::~UByteArray() { free(_array); }

FileInputStream::FileInputStream(File &file) : _s(new ifstream) {
    _s->open(file.getAbsolutePath(), std::ios::in | std::ios::app);
}

FileInputStream::FileInputStream(char *dir, char *name) {
    File file(dir, name);
    _s->open(file.getAbsolutePath(), std::ios::in | std::ios::app);
}

FileInputStream::~FileInputStream() {
    delete (_s);
}

int FileInputStream::read(ByteArray &b) {
    streamsize len = -1;
    if (_s->eof() == 0) {//到达结尾返回非零
        _s->read(b, b.size());
        len = _s->gcount();
    }
    return int(len);
}

void FileInputStream::close() {
    _s->close();
}

FileOutputStream::FileOutputStream(File &file) : _s(new ofstream) {
    _s->open(file.getAbsolutePath(), std::ios::out | std::ios::app);
}

FileOutputStream::FileOutputStream(char *dir, char *name) {
    File file(dir, name);
    _s->open(file.getAbsolutePath(), std::ios::out | std::ios::app);
}

FileOutputStream::~FileOutputStream() {
    delete (_s);
}

void FileOutputStream::close() {
    _s->close();
}

TextFile::TextFile(File &file) {
    _is = new FileInputStream(file);
    _os = new FileOutputStream(file);
}

TextFile::TextFile(char *dir, char *name) {
    _is = new FileInputStream(dir, name);
    _os = new FileOutputStream(dir, name);
}

TextFile::TextFile(char *path) {
    File file(path);
    _is = new FileInputStream(file);
    _os = new FileOutputStream(file);
}

String &TextFile::getText() {
    StringBuilder builder;
    ByteArray bytes(64 * 1024);
    int len;
    while ((len = _is->read(bytes)) != -1) {
        builder.append(bytes, 0, len);
    }
    return builder.toString();
}

TextFile::~TextFile() {
    delete _is;
    delete _os;
}

void TextFile::close() {
    _is->close();
    _os->close();
}

File::File(char *path) {
    _path = new String(path);
}

File::File(char *dir, char *name) {
    StringBuilder builder;
    _path = &(builder.append(dir).append(name).toString());
}

String &File::getAbsolutePath() {
    return *_path;
}

File::~File() {
    delete _path;
}

bool File::exists() {
    fstream file;
    file.open(*_path, ios_base::in);
    bool result = file.is_open();
    file.close();
    return result;
}