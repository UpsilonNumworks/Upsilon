// #pragma GCC push_options
// #pragma GCC optimize ("O0")

#include <poincare/init.h>
#include <poincare/expression.h>
#include <poincare/integer.h>
#include <poincare/tree_pool.h>

#include <gint/display.h>
#include <gint/keyboard.h>

namespace Poincare {

// class TreePool final {
// public:
//   static void RegisterPool(TreePool * pool) {
//     dclear(C_WHITE); dtext(1, 16, C_BLACK, "Fake class call"); dupdate(); getkey();
//   }
// private:
//   constexpr static int BufferSize = 16384 / 4;
//   constexpr static int MaxNumberOfNodes = BufferSize/sizeof(TreeNode);
//   constexpr static int k_maxNodeOffset = BufferSize/ByteAlignment;
  
//   uint16_t m_availableIdentifiers[MaxNumberOfNodes];
// };

void Init() {
  dclear(C_WHITE); dtext(1, 16, C_BLACK, "In Poincare init"); dupdate(); getkey();

  // dclear(C_WHITE); dtext(1, 16, C_BLACK, "Created fake pool"); dupdate(); getkey();
  // static TreePool fakePool;
  // dclear(C_WHITE); dtext(1, 16, C_BLACK, "Calling fake class"); dupdate(); getkey();
  // TreePool::RegisterPool(&fakePool);

  // Create and register the shared static pool
  static TreePool pool;

  dclear(C_WHITE); dtext(1, 16, C_BLACK, "Created pool"); dupdate(); getkey();

  Poincare::TreePool* poolPtr = &pool;
  dclear(C_WHITE); dtext(1, 16, C_BLACK, "Address taken"); dupdate(); getkey();
  TreePool::RegisterPool(poolPtr);
  // pool.RegisterPool(poolPtr);

  // 37445c:       d7 20           mov.l   3744e0 <__ZN8Poincare4InitEv+0x134>,r7  ! 73fca
  // 374462:       07 03           bsrf    r7

    // dclear(C_WHITE); dtext(1, 16, C_BLACK, "Registering pool"); dupdate(); getkey();
    // if (pool.SharedStaticPool == nullptr) {
    //   dclear(C_WHITE); dtext(1, 16, C_BLACK, "SharedStaticPool null"); dupdate(); getkey();
    // } else {
    //   dclear(C_WHITE); dtext(1, 16, C_BLACK, "SharedStaticPool not null"); dupdate(); getkey();
    // }
    // assert(pool.SharedStaticPool == nullptr);
    // dclear(C_WHITE); dtext(1, 16, C_BLACK, "Asserted"); dupdate(); getkey();
    // pool.SharedStaticPool = poolPtr;
    // dclear(C_WHITE); dtext(1, 16, C_BLACK, "Set pool"); dupdate(); getkey();

  dclear(C_WHITE); dtext(1, 16, C_BLACK, "Registered pool"); dupdate(); getkey();
}

void Tidy() {
  // Clean Expression (reset the SymbolReplacementsLock)
  Expression::Tidy();
}

}

// #pragma GCC pop_options
