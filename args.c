#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "args.h"

#define NOOPTION NULL



option_t* opt_void(option_t* l, const char* kw, void (*f)()){
    option_t* nouvelElement = malloc(sizeof(option_t));
    nouvelElement->keyword = kw;
    nouvelElement->spec=OptVoid;
    nouvelElement->fct.opt_void=f;
    nouvelElement->next = NULL;
    if(l == NULL)
  {
        return nouvelElement;
   }
    else
   {
       option_t* temp=l;
       while(temp->next != NULL)

        {
         temp = temp->next;

        }
        temp->next = nouvelElement;
        return l;
     }

}
///////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
option_t* opt_2int(option_t* l, const char* kw, void (*f)(int,int)){

    option_t* nouvelElement = malloc(sizeof(option_t));
    nouvelElement->keyword=kw;
    nouvelElement->spec=Opt_2Int;
    nouvelElement->fct.opt_2int=f;
    nouvelElement->next = NULL;
 if(l == NULL)
  {
      return nouvelElement;
     }

    else
   {
     option_t* temp=l;
     while(temp->next != NULL)

        {
          temp = temp->next;

        }

        temp->next = nouvelElement;
         return l;
     }
}
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
option_t* opt_int(option_t* l, const char* kw, void (*f)(int)){

    option_t* nouvelElement = malloc(sizeof(option_t));
    nouvelElement->keyword=kw;
    nouvelElement->spec=OptInt;
    nouvelElement->fct.opt_int=f;
    nouvelElement->next = NULL;
 if(l == NULL)
  {
      return nouvelElement;

    }
  else
    {
      option_t* temp=l;
       while(temp->next != NULL)

        {
           temp = temp->next;

        }

        temp->next = nouvelElement;

        return l;

    }

}


option_t* opt_float(option_t* l, const char* kw, void (*f)(float)){

    option_t* nouvelElement = malloc(sizeof(option_t));
 
   
    nouvelElement->keyword=kw;
    nouvelElement->spec=OptFloat;
    nouvelElement->fct.opt_float=f;
 
    
    nouvelElement->next = NULL;
 
   if(l == NULL)

    {
    return nouvelElement;
}

    else

    {
        option_t* temp=l;
        while(temp->next != NULL)
      {
        temp = temp->next;
         }
        temp->next = nouvelElement;
        return l;
    }
}
///////////////////////////////////////////////////////////////////////////////
option_t* opt_string(option_t* l, const char* kw, void (*f)(const char*)){

    option_t* nouvelElement = malloc(sizeof(option_t));
    nouvelElement->keyword=kw;
    nouvelElement->spec=OptString;
    nouvelElement->fct.opt_str=f;
 
    
    nouvelElement->next = NULL;
 
    if(l == NULL)

    {
        return nouvelElement;
    }
       else
    {  
        option_t* temp=l;
        while(temp->next != NULL)

        {
            temp = temp->next;
       }
        temp->next = nouvelElement;
        return l;
    }
}
void opt_delete(option_t* l){
free(l);
}
///////////////////////////////////////////////////////////////////
//////////////////////////////////////
void process_arguments(option_t * l, int argc, char * *argv)
{
    int pos_arg = 1;
    int temp = 0;
    while (pos_arg < argc) {
	option_t *pos_opt = l;
	while (pos_opt != NULL
	       && strcmp(argv[pos_arg], pos_opt->keyword)) {
	    pos_opt = pos_opt->next;
	}
	if (pos_opt == NULL) {
	    printf("Pas trouve\n");
	} else {
	    // execution de la fonction
	    switch (pos_opt->spec) {
             case Opt_2Int:
                 temp = pos_arg+2;
		 pos_opt->fct.opt_2int(atoi(argv[++pos_arg]),atoi(argv[temp]));
                    pos_arg++;
		break;
	    case OptVoid:
		pos_opt->fct.opt_void();
		break;
	    case OptInt:
		pos_opt->fct.opt_int(atoi(argv[++pos_arg]));
		break;
	    case OptString:
		pos_opt->fct.opt_str(argv[++pos_arg]);
		break;
	    case OptFloat:
		pos_opt->fct.opt_float(atof(argv[++pos_arg]));
		break;
	    default:
		printf("Ca n'arrivera jamais ici");
	    }
	}
	pos_arg++;
    }
}
