#ifndef PERMISSION_H
#define PERMISSION_H

//权限类定义
class Permission
{
protected:
	bool access_permission;				//访问权限，即用户是否可以访问系统（用于黑名单功能）
	bool modified_admin_permission;		//管理用户权限，主要包括加新用户、删除已有用户、修改用户密码
	bool check_permission;				//查看权限，即用户是否可以查看反馈
	bool modified_food_permission;		//管理菜色权限，即用户是否可以添加、修改、删除菜色
	bool view_food_permission;			//查看菜色权限
	bool submit_permission;				//提交反馈权限
	bool search_permission;				//搜索权限
public:
	Permission(bool access_permission,
		bool modified_admin_permission,
		bool check_permission,
		bool modified_food_permission,
		bool view_food_permission,
		bool submit_permission,
		bool search_permission) :
		access_permission(access_permission),
		modified_admin_permission(modified_admin_permission),
		modified_food_permission(modified_food_permission),
		check_permission(check_permission),
		view_food_permission(view_food_permission),
		submit_permission(submit_permission),
		search_permission(search_permission) {};
	bool WhetherAccess() { return access_permission; };
	bool WhetherModifiedFood() { return modified_food_permission; };
	bool WhetherModifiedAdmin() { return modified_admin_permission; };
	bool WhetherCheck() { return check_permission; };
	bool WhetherViewFood() { return view_food_permission; };
	bool WhetherSubmit() { return submit_permission; };
	bool WhetherSearch() { return search_permission; };
};

extern Permission admin_permission;			//管理员权限
extern Permission user_permission;			//普通用户权限
extern Permission black_permission;			//黑名单用户权限


#endif // !_PERMISSION_H_
