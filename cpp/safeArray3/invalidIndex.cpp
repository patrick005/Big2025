#include "invalidIndex.h"

InvalidIndex::InvalidIndex(int index)
: index_(index)
{

}


InvalidIndex::invalid() const
{
    return index_;
}



