#include

typedef struct stacknode{
	int val;
	struct stacknode *next;
}STACK;

static STACK *stack = NULL;


void STACKinit(int size){
	if(head!=NULL){
		STACKclean(head);
	}
}

int STACKempty(){
	return(head==NULL);
}

void STACKpush(int val){
	STACK* newNode =  mallock(size(stack))
	newNode -> val = val;
	newNode -> next = head;
	head = newNode;
}

int STACKpop(){
	int res = head -> val;
	STACK *temp=head;
	head = head -> next;
	free(temp);
	return res;
}

int STACKsize()
void STACKclean(STACK *head){}
