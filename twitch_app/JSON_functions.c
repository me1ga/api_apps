#include "JSON_structures.h"

void RemoveHeaders(char * string, int len){
	char *p = NULL;
	int plen = 0, last_s = 0;
	p = memchr(string, 123, len); //123 = "{"
	plen = strlen(p);
	for( last_s = plen ; last_s > 1 ; last_s-- ){
		if( 125 == p[last_s-1] ) break; //125 = "}"
	}
	char buffer[2048];
	memset(buffer, 0, sizeof(buffer));
	memcpy(buffer, p, last_s);
	memset(string, 0, len);
	memcpy(string, buffer, strlen(buffer));
}

void Clean_links_v3(struct _links * _links){
	memset(&(_links->chat), 0, sizeof(_links->chat));
	memset(&(_links->commercial), 0, sizeof(_links->commercial));
	memset(&(_links->editors), 0, sizeof(_links->editors));
	memset(&(_links->features), 0, sizeof(_links->features));
	memset(&(_links->follows), 0, sizeof(_links->follows));
	memset(&(_links->next), 0, sizeof(_links->next));
	memset(&(_links->self), 0, sizeof(_links->self));
	memset(&(_links->stream_key), 0, sizeof(_links->stream_key));
	memset(&(_links->subscriptions), 0, sizeof(_links->subscriptions));
	memset(&(_links->videos), 0, sizeof(_links->videos));
}

void CleanNotifications_v3(struct notifications * notifications){
	memset(&(notifications->email), 0, sizeof(notifications->email));
	memset(&(notifications->push), 0, sizeof(notifications->push));
}

void CleanUser_v3(struct user * user){
	memset(&(user->type), 0, sizeof(user->type));
	memset(&(user->name), 0, sizeof(user->name));
	memset(&(user->created_at), 0, sizeof(user->created_at));
	memset(&(user->updated_at), 0, sizeof(user->updated_at));
	Clean_links_v3(&(user->_links));
	memset(&(user->logo), 0, sizeof(user->logo));
	user->_id = 0;
	memset(&(user->display_name), 0, sizeof(user->display_name));
	memset(&(user->email), 0, sizeof(user->email));
	memset(&(user->partnered), 0, sizeof(user->partnered));
	memset(&(user->bio), 0, sizeof(user->bio));
	CleanNotifications_v3(&(user->notifications));
}

struct _links Parse_links_v3(char * string){
	struct _links _links;
	Clean_links_v3(&_links);
	return _links;
}

struct user ParseUser_v3(char * string){
	struct user user;
	int i;
	char *p = NULL;
	CleanUser_v3(&user);
	p = strstr(string, "\"display_name\"");
	if (NULL == p){
		/* code */
	}else{
		for(i = 16; i < strlen(p); i++){
			if( 34 == p[i] ){ // 34 == "
				memcpy(&(user.display_name), (p+16), i-16);
				break;
			}
		}
	}
	return user;
}
