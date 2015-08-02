//  File:       JSON_structures.h
//  Autor:      me1ga
//  Created:    2 август 2015 г. 14:25

#ifndef JSON_STRUCTURES_H
#define JSON_STRUCTURES_H

#ifdef  __cplusplus
extern "C" {
#endif

#define STR_LEN 256
#define TYPE_STR_LEN 16
#define DATE_STR_LEN 21

//1-th level
struct _links{
	char chat[STR_LEN];
	char commercial[STR_LEN];
	char editors[STR_LEN];
	char features[STR_LEN];
	char follows[STR_LEN];
	char next[STR_LEN];
	char self[STR_LEN];
	char stream_key[STR_LEN];
	char subscriptions[STR_LEN];
	char videos[STR_LEN];
};

struct notifications{
	char email;
	char push;
};

//2-nd level
struct user{
	char type[TYPE_STR_LEN];
	char name[STR_LEN];
	char created_at[DATE_STR_LEN];
	char updated_at[DATE_STR_LEN];
	struct _links _links;
	char logo[STR_LEN];
	unsigned long int _id;
	char display_name[STR_LEN];
	char email[STR_LEN];
	char partnered;
	char bio[STR_LEN];
	struct notifications notifications;
};

#ifdef  __cplusplus
}
#endif
#endif  /* JSON_STRUCTURES_H */
