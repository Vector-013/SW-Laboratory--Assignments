/*
AUTHOR : OJAS DUBEY
ROLL NUMBER : 22CS30039

STRUCTS :

1. location - double location of 2D coordinates
2. conn_node - Node in the linked list of user connections. User connections are also used to keep track of posters for a given Post.
3. post_node - Node in the linked list of posts. Stores postal index and pointer to next node.
4. node - Main node storing all of user data as seen in the struct including User ID, type, linked list of connections,
          date of creation, linked list of posts and other info.
5. post - Stores Post ID, post content, and linked list of people who posted it

GLOBAL VARIABLES
1. node *USER_DB              array storing all the user data
2. post *POSTS_DB             array storing data of all posts and users who posted them
3. int DB_SIZE                isize of User database
4, int POSTS_NUM              size of posts array

FUNCTIONS :

1. void push(conn_node **head, int id);
   void print_list(conn_node **head);
   void delete_from_list(conn_node **head, int uid);

   These functions are linked list functions related to the list of user connections and posters of a post.
   "push" is used to add items to the list, print_list prints the content of the list by accesing the global
   database of users. delete_from_list clears out the user data from both the USER_DB and any refernce in the
   posters list too.

2. void init();
   Initialises the USER_DB.

   This step is essential as it begins the pointer of USER_DB via the realloc method.
   An empty user is created and their UID is set to -1.

3. int find_min_pos()
   Returns first empty position in the USER_DB.

   In order to insert a user in the USER_DB without wasting memory by extra allocation, We find an empty slot
   in the USER_DB (a slot can be empty if someone deleted from it").

4. void add_to_DB(node* new)
   Adds the user "new" to the USER_DB, assigns it a uid.

   Uses the min_pos returned by find_min_pos(), assigns the index as a UID to the new user. In case there is no
   spot, the last empty position is given to the new user and the USER_DB is realloc ed to a size 1 greater.

5. void init_posts()
   Initialises the USER_DB.
   Similar to init() in function, except operates upon POSTS_DB.

6. int find_min_post_pos()
   Returns first empty position in the USER_DB.
   Similar to find_min_pos() in functionality.

7. void add_to_POSTS_DB(post *new)
   Adds the post "new" to the POSTS_DB, assigns it a pid.

   Uses the find_min_pos_posts() to check wether realloc is required based upon the location of the empty position
   in the POSTS_DB. If the empty position is the last in POSTS_DB then realloc is doe to increase the size of the
   array by 1.

8. void create_post()
   Creates a post and calls add_to_POSTS_DB.

   The function takes a UID to create a post and the poster is added to the list of posters regarding the pid of
   the post created.The post is added in the list of the user's posts as well. Data sanitization is implemented
   to prevent the Input of an invalid UID either if the user inputs non-int data or the UID is invalid.
   This is a recurring concept in this programme.

9. void repost()
   Reposts a post based on the uid and pid entered.

   User input sanitization for both uid and pid are applied. That would prevent any invalid input or non-int input
   to be invalidated and user is prompted again. Rest of the functionality is much like create_post().

10.void DOB_input_and_validity(char date_str[])
   Modifies the char datestr[] into a formatted date string
   Sanitization and input function for dates

   Sanitization is done for year, month, day in that order. Attention has been given to number of days in the month,
   which is why month is taken as a input before day. getchar in a while loop is used multiple time across the code
   to clear buffer. sprintf() function is used to format int date to a string.

11.bool connect(int user1, int user2)
   returns boolean regarding the possibility of user1 user2 forming a connection.
   If true, adds the users in each others connection list as well.

12.void create_user()
   Creates a user in the USER_DB.

   Prompts user type of user accuount needed, Uses data sanitization to check validity of the choice provided by
   the user. Uses "time.h" library to stamp current date-time on the creation time. Uses library asctime() function
   to convert this date-time to a string and store it in the user node. Asks the Type-specific data like DOB and
   location, using input sanitization in both these, then assigns these to the user node.

13.void form_connections()
   creates connections using auxillary function connect()

   prompts for two UIDs to connect with data sanitization. Checks validity based on the instructions in connect().
   If valid, connection is created and the users are pushed in each others linked lists.
   If invalid, User is given the option to try again or quit.

14.void delete_user()
   deletes the account of a user from the USER_DB

   Prompts for UID to be deleted. employs linked list method delete_from_list() to delete, it clears the user from
   both the USER_DB and any posters list it might be in.

15.void search_user_by_filter()
   Searches and lists out users based on either of three parameters.

   Prompts user for any of the 3 filters to search from, Uses data sanitization method to ensure validity of the
   choice. If user chooses Name, string with possibily spaces is taken as an input and matched against names in the
   User_DB. similar implementation for matching by type and DOB is initiated, as DOB is a string same method can be
   used to compare all three types of filters.

16.bool is_substring(char *s1, char *s2)
   Simple auxillary function to check wether s1 is a substring of s2.

17.void post_search()
   Prompts for content too search across POSTS_DB. Using auxillary function of is_substring() to check for substrings
   and lists out all posts which contain input as a substring.

18.void individual_link_print()
   Prints all individuals linked via a Group or an Organisation

   Prompts UID with sanitization, Traverses linked list of connections looking for users with type of Group or Organisation
   If such users are found, Their connections list is traversed looking for Individuals. In case of a match, The data is
   logged on the console.

19.void print_1_hop()
   Prints all users linked to a user
   Prompts for a uid with sanitization, traverses the linked list of connections and logs them to the console.

20.void print_DB()
   Simple function to print entire data of the USER_DB in a tabular manner. Prints all attributes of each user.

21.void print_POSTS_DB()
   Similar to print_DB, prints all the data of POSTS_DB, including list of users who posted a certain post.

22.void menu()
   Provides the user interface as mentioned in the instructions. Consists of 11 prompts which use the various functions
    mentioned above.
*/
#include <stdlib.h>
#include <stdbool.h>
typedef struct location
{
   double x;
   double y;
} location;

typedef struct _conn_node
{
   int uid;
   struct _conn_node *next;

} conn_node;

typedef struct _post_node
{
   int pid;
   struct _post_node *next;

} post_node;

typedef struct _node
{
   int id;
   char type;
   char name[100];
   conn_node *connections;
   char *creation_date;
   char dob[11];
   bool dob_choice;
   location loc;
   post_node *posts;
} node;

typedef struct _post
{
   int pid;
   char post[300];
   conn_node *posters;

} post;

void push(conn_node **head, int id);
void print_list(conn_node **head);
void delete_from_list(conn_node **head, int uid);
void push_post(post_node **head, int pid);
void print_posts(post_node **head);
void delete_from_posts(post_node **head, int pid);
void init();
int find_min_pos();
void add_to_DB(node *new);
void init_posts();
int find_min_post_pos();
void add_to_POSTS_DB(post *new);
void create_post();
void repost();
void DOB_input_and_validity(char date_str[]);
bool connect(int user1, int user2);
void create_user();
void form_connections();
void delete_user();
void search_user_by_filter();
bool is_substring(char *s1, char *s2);
void post_search();
void individual_link_print();
void print_1_hop();
void print_DB();
void print_POSTS_DB();
void menu();
