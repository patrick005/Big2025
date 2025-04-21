#ifndef INVALID_INDEX_H
#define INVALID_INDEX_H

class InvalidIndex {
private:
    int index_;


public:
    InvalidIndex(int index);

    int invalid() const;


};



InvalidIndex::InvalidIndex(int index)
: index_(index)
{

}


InvalidIndex::invalid() const
{
    return index_;
}



#endif