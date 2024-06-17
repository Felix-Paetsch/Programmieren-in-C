#include <stdio.h>
#include "pool.h"

THUNK(custom_drop, const char* msg) {
	printf("%s\n", msg);
}

int main(void) {
	Pool pool = poolNew();
	
	SCOPE(&pool) {
		poolRegister(&pool, "outer drop #1", &custom_drop);
		
		SCOPE(&pool) {
			poolRegister(&pool, "inner drop #1", &custom_drop);
			
			SCOPE(&pool) {
				poolRegister(&pool, "innermost drop #1", &custom_drop);
				poolRegister(&pool, "innermost drop #2", &custom_drop);
			}
			
			poolRegister(&pool, "inner drop #2", &custom_drop);
		}
		
		poolRegister(&pool, "outer drop #2", &custom_drop);
	}
	
	poolDrop(&pool);
	return 0;
}
