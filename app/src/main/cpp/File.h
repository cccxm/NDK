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

#ifndef NDK_FILE_H
#define NDK_FILE_H

class String;

class ByteArray;

class File;

//typedef ifstream;
//typedef ofstream;

class InputStream {
public:
    virtual int read() { return -1; }

    virtual int read(ByteArray &b) { return -1; }

    virtual int read(ByteArray &b, int off, int len) { return -1; }

    virtual long skip(long n) { return 0; }

    virtual int available() { return 0; }

    virtual void close() { }
};

class OutputStream {
public:
    virtual void write(int b){};

    virtual void write(ByteArray &b) { }

    virtual void write(ByteArray &b, int off, int len) { }

    virtual void flush() { }

    virtual void close() { }
};

class FileInputStream : public InputStream {
    ifstream *_s;
public:
    FileInputStream(File &file);

    FileInputStream(char *dir, char *name);

    ~FileInputStream();

    virtual int read() { return -1; }

    virtual int read(ByteArray &b);

    virtual int read(ByteArray &b, int off, int len) { return -1; }

    virtual long skip(long n) { return 0; }

    virtual int available() { return 0; }

    virtual void close();
};

class FileOutputStream : public OutputStream {
    ofstream *_s;
public:
    FileOutputStream(File &file);

    FileOutputStream(char *dir, char *name);

    ~FileOutputStream();

    virtual void write(int b) { }

    virtual void write(ByteArray &b) { }

    virtual void write(ByteArray &b, int off, int len) { }

    virtual void flush() { }

    virtual void close();
};

class File {
    String *_path;
    bool _isFile;
    bool _isDirectory;
public:
    File(char *fName);

    File(char *dir, char *name);

    ~File();

    bool createNewFile() { return false; }

    bool deleteFile() { return false; }

    bool exists();

    bool makedir() { return false; }

    bool makedirs() { return false; }

    String &getAbsolutePath();

    bool isDirectory() { return _isDirectory; }

    bool isFile() { return _isFile; }

    bool setExecutable(bool executable) { return false; }

    bool setReadable(bool readable) { return false; }

    bool setWritable(bool writable) { return false; }
};

class TextFile {
    InputStream *_is;
    OutputStream *_os;
public:
    TextFile(File &file);

    TextFile(char *dir, char *name);

    TextFile(char *path);

    ~TextFile();

    void append(char *str) { }

    String &getText();

    void close();
};

#endif //NDK_FILE_H
