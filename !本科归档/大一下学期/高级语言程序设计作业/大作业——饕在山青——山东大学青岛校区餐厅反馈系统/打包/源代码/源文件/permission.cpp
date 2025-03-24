#include"permission.h"

Permission admin_permission(true, true, true, true, true, true, true);					//管理员权限
Permission user_permission(true, false, false, false, true, true, true);				//普通用户权限
Permission black_permission(false, false, false, false, false, false, false);			//黑名单用户权限