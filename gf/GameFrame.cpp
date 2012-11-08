#include "gf/GameFrame.h"

#include <assert.h>

#include "HashSet.h"

int main(int argc, char* argv[]) {
    gf::HashSet<int> hashSet;

    assert(hashSet.size() == 0);
    assert(hashSet.empty());
    assert(!hashSet.contains(0));
    assert(!hashSet.contains(1));
    assert(!hashSet.contains(-1));

    assert(hashSet.add(0));
    assert(hashSet.contains(0));
    assert(!hashSet.contains(1));
    assert(!hashSet.contains(-1));
    assert(hashSet.size() == 1);
    assert(!hashSet.empty());

    assert(hashSet.add(1));
    assert(hashSet.contains(0));
    assert(hashSet.contains(1));
    assert(!hashSet.contains(-1));
    assert(hashSet.size() == 2);
    assert(!hashSet.empty());
    
    assert(!hashSet.add(0));
    assert(!hashSet.add(1));

    assert(hashSet.remove(0));
    assert(hashSet.size() == 1);
    assert(!hashSet.empty());
    assert(!hashSet.contains(0));
    assert(!hashSet.remove(0));
    assert(hashSet.size() == 1);
    assert(!hashSet.empty());


}

namespace gf {

    GameFrame::GameFrame()
    {
    }


    GameFrame::~GameFrame()
    {
    }

}
