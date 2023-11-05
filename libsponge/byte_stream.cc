#include "byte_stream.hh"
#include<iostream>

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`



using namespace std;

ByteStream::ByteStream(const size_t capacity):_capacity(capacity+1),_buffer(string(capacity,' ')),remain_capacity(capacity),
nwrite(0),nread(0),end(false),writen(0),readed(0),_error(false) { 

}

size_t ByteStream::write(const string &data) {
    size_t len = data.length();
    if(data.length()>remain_capacity){
        set_error();
        len = remain_capacity;
        cout<<len;
    }
    for(size_t i= 0;i<len;i++){
        _buffer[(nwrite) % _capacity] = data[i];
        nwrite++;
        nwrite %= _capacity;
    }
    writen+=len;
    remain_capacity -= len;
    return len;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    string temp = "";
    for(size_t i = 0;i<len;i++){
        temp += _buffer[(i+nread) % _capacity];
    }

    return temp;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { 
    nread += len;
    nread %= _capacity;
    remain_capacity += len;
    readed += len;
 }

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string out_string;
    for(size_t i = 0;i<len;i++){
        out_string += _buffer[(nread) % _capacity];
        nread++;
        nread %= _capacity;
    }
    readed+= len;
    remain_capacity+=len;
    return out_string;
}

void ByteStream::end_input() {
    end = true;
    return;
}

bool ByteStream::input_ended() const { 
    return end;
}

size_t ByteStream::buffer_size() const { 
    return _capacity-remain_capacity-1;
}

bool ByteStream::buffer_empty() const {
    return nread == nwrite;
 }

bool ByteStream::eof() const { 
    return input_ended() && buffer_empty();
}

size_t ByteStream::bytes_written() const { 
    return writen;
}

size_t ByteStream::bytes_read() const { 
    return readed;
}

size_t ByteStream::remaining_capacity() const { 
    return remain_capacity;

}
