#include <stdio.h>
#include <stdbool.h>
#include "social.h" // including header file
#include <time.h>   // Used to fetch the current date and time using
#include <string.h>

node *USER_DB;      // array storing all the user data
post *POSTS_DB;     // array storing data of all posts and users who posted them
int DB_SIZE = -1;   // isize of User database
int POSTS_NUM = -1; // size of posts array

// -------------------------------------------------[CONN LINKED LIST FUNCTNS]------------------------------------------------------

void push(conn_node **head, int id)
{
    conn_node *new = (conn_node *)malloc(sizeof(conn_node));
    new->uid = id;

    new->next = *head;
    *head = new;
}

void print_list(conn_node **head)
{
    conn_node *temp = *head;
    if (temp == NULL)
    {
        printf("Empty connections!!\n");
        return;
    }

    while (temp)
    {
        printf("[USER #%d %s] -> ", (temp)->uid, USER_DB[temp->uid].name);
        (temp) = (temp)->next;
    }

    printf("\n");
}

void delete_from_list(conn_node **head, int uid)
{
    conn_node *temp = *head;
    conn_node *prev = temp;
    if (temp == NULL)
    {
        return;
    }

    if ((*head)->uid == uid)
    {
        *head = (*head)->next;
        free(temp);
        return;
    }

    while (temp)
    {
        if (temp->uid == uid)
        {
            prev->next = temp->next;
            free(temp);
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    return;
}

// -------------------------------------------------[POST LINKED LIST FUNCTNS]------------------------------------------------------
void push_post(post_node **head, int pid)
{
    post_node *new = (post_node *)malloc(sizeof(post_node));
    new->pid = pid;

    new->next = *head;
    *head = new;
}

void print_posts(post_node **head)
{
    post_node *temp = *head;
    if (temp == NULL)
    {
        printf("Empty posts!!\n");
        return;
    }

    while (temp)
    {
        printf("[POST #%d ] -> ", (temp)->pid);
        (temp) = (temp)->next;
    }

    printf("\n");
}

void delete_from_posts(post_node **head, int pid)
{
    post_node *temp = *head;
    post_node *prev = temp;
    if (temp == NULL)
    {
        return;
    }

    if ((*head)->pid == pid)
    {
        *head = (*head)->next;
        free(temp);
        return;
    }

    while (temp)
    {
        if (temp->pid == pid)
        {
            prev->next = temp->next;
            free(temp);
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    return;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------[USER_DB FUNCTNS]-----------------------------------------------------------------
void init()
{
    USER_DB = (node *)realloc(USER_DB, sizeof(node) * 1);
    USER_DB[0].id = -1;
    DB_SIZE++; // DB_SIZE is idx of last pos which can be accessed (empty for sure) (number of elements id DB_SIZE +1)
}

int find_min_pos()
{
    int i = 0;
    while (i <= DB_SIZE && USER_DB[i].id != -1)
    {
        i++;
    }
    if (i >= 0)
        return i;

    return -1;
}

void add_to_DB(node *new)
{
    // printf("SZ: %d and %d\n", DB_SIZE, find_min_pos());
    if (find_min_pos() != DB_SIZE)
    {
        // printf("miyn : %d\n", find_min_pos());
        new->id = find_min_pos();
        USER_DB[find_min_pos()] = *new;
    }

    else
    {
        USER_DB = (node *)realloc(USER_DB, sizeof(node) * (DB_SIZE + 2));
        // printf("min : %s\n", (*new).name);
        new->id = DB_SIZE;
        USER_DB[DB_SIZE] = *new;

        DB_SIZE++;
        USER_DB[DB_SIZE].id = -1;
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------[POSTING]-----------------------------------------------------------------
void init_posts()
{
    POSTS_DB = (post *)realloc(POSTS_DB, sizeof(post) * 1);
    POSTS_DB[0].pid = -1;
    POSTS_NUM++; // DB_SIZE is idx of last pos which can be accessed (empty for sure) (number of elements id DB_SIZE +1)
}

int find_min_post_pos() // finding minimum empty spot to fill in the new user
{
    int i = 0;
    while (i <= POSTS_NUM && POSTS_DB[i].pid != -1)
    {
        i++;
    }
    if (i >= 0)
        return i;

    return -1;
}

void add_to_POSTS_DB(post *new) // adding user to min position available
{
    if (find_min_post_pos() != POSTS_NUM)
    {
        new->pid = find_min_post_pos();
        POSTS_DB[find_min_post_pos()] = *new;
    }

    else
    {
        POSTS_DB = (post *)realloc(POSTS_DB, sizeof(post) * (POSTS_NUM + 2));
        new->pid = POSTS_NUM;
        POSTS_DB[POSTS_NUM] = *new;

        POSTS_NUM++;
        POSTS_DB[POSTS_NUM].pid = -1;
    }
}

void create_post()
{
    int uid;
    post new;
    new.posters = NULL;

    printf("Enter your UID : ");
    while (true) // UID sanitization
    {
        if ((scanf(" %d", &uid) == 1) && uid >= 0 && uid < DB_SIZE && USER_DB[uid].id != -1)
        {
            break;
        }
        else
        {
            printf("[INVALID UID...TRY AGAIN]\n");
            printf("Enter your UID : ");
            while (getchar() != '\n')
                ;
        }
    }

    printf("Enter the content of your post [MAX CHARS : 300] : ");
    scanf(" %[^\n]s", new.post);

    add_to_POSTS_DB(&new);
    push_post(&(USER_DB[uid].posts), new.pid);
    push(&(POSTS_DB[new.pid].posters), uid);

    // push(&(POSTS_DB[new.pid].posters), uid);

    printf("[YOUR POST HAS BEEN ADDED. POST ID #%d]\n", new.pid);
    return;
}

void repost()
{
    int uid;
    int pid_to_repost;

    printf("Enter your UID : ");
    while (true) // UID sanitization
    {
        if (scanf(" %d", &uid) == 1 && uid >= 0 && uid < DB_SIZE && USER_DB[uid].id != -1)
        {
            break;
        }
        else
        {
            printf("[INVALID UID...TRY AGAIN]\n");
            printf("Enter your UID : ");
            while (getchar() != '\n')
                ;
        }
    }

    printf("Enter the postal id of post you would like to repost(pid) : ");
    while (true) // PID sanitization                                                       // PID sanitization
    {
        if (scanf(" %d", &pid_to_repost) == 1 && pid_to_repost >= 0 && pid_to_repost < POSTS_NUM && POSTS_DB[pid_to_repost].pid != -1)
        {
            break;
        }
        else
        {
            printf("[INVALID UID...TRY AGAIN]\n");
            printf("Enter your UID : ");
            while (getchar() != '\n')
                ;
        }
    }

    push_post(&(USER_DB[uid].posts), pid_to_repost);
    push(&(POSTS_DB[pid_to_repost].posters), uid);

    printf("[REPOSTED #%d SUCCESFULLY]\n", pid_to_repost);
    return;
}

//-------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------[USER]---------------------------------------------------------------------

void DOB_input_and_validity(char date_str[])
{
    int day, month, year;
    printf("Enter D.O.B.(three ints, day, month, year) :\n");

    bool day_bool = true, month_bool = true, year_bool = true;

    while (year_bool)
    {
        printf("Enter the year as an integer [YEAR > 1900 & YEAR < 2024] : ");
        if (scanf("%d", &year) == 1)
        {
            if (year < 1900)
            {
                printf("[INVALID YEAR...TRY AGAIN]\n");
                while (getchar() != '\n')
                    ;
                continue;
            }
            else if (year > 2024)
            {
                printf("[INVALID YEAR...TRY AGAIN]\n");
                while (getchar() != '\n')
                    ;
                continue;
            }
            else
            {
                year_bool = false;
            }
        }
        else
        {
            printf("[INVALID YEAR...TRY AGAIN]\n");
            while (getchar() != '\n')
                ;
        }
    }

    while (month_bool)
    {
        printf("Enter the month as an integer : \n");
        if (scanf("%d", &month) == 1)
        {
            if (month > 12 || month < 1)
            {
                printf("[INVALID MONTH...TRY AGAIN]\n");
                while (getchar() != '\n')
                    ;
                continue;
            }
            else
            {
                month_bool = false;
            }
        }
        else
        {
            printf("[INVALID MONTH...TRY AGAIN]\n");
            while (getchar() != '\n')
                ;
        }
    }

    while (day_bool)
    {
        printf("Enter the date of the month as an integer: \n");
        if (scanf("%d", &day) == 1)
        {
            if (day < 1 || day > 31)
            {
                printf("[INVALID DAY...TRY AGAIN]\n");
                while (getchar() != '\n')
                    ;
                continue;
            }
            if (month == 4 || month == 6 || month == 9 || month == 11)
            {
                if (day > 30)
                {
                    printf("[INVALID DAY...TRY AGAIN]\n");
                    while (getchar() != '\n')
                        ;
                    continue;
                }
            }
            if (month == 2)
            {
                if (day > 29)
                {
                    printf("[INVALID DAY...TRY AGAIN]\n");
                    while (getchar() != '\n')
                        ;
                    continue;
                }
            }
            else
            {
                day_bool = false;
            }
        }
        else
        {
            printf("[INVALID DATE...TRY AGAIN]\n");
            while (getchar() != '\n')
                ;
        }
    }

    sprintf(date_str, "%02d/%02d/%04d", day, month, year); // string formatter
}

bool connect(int user1, int user2)
{
    bool connect_demand = true;
    char type1 = USER_DB[user1].type, type2 = USER_DB[user2].type;

    if ((type1 == 'I' && type2 != 'I') || (type1 != 'I' && type2 == 'I') || (type1 == 'B' && type2 == 'G') || (type1 == 'G' && type2 == 'B'))
    {
        push(&(USER_DB[user1].connections), user2); // push into each others linked list of connections
        push(&(USER_DB[user2].connections), user1);
        printf("[ADDED CONNECTION]\n");
        return true;
    }
    else
    {
        printf("Incompatible connection, Try again\n");
    }
    return false;
}

void create_user()
{
    node new; // new user
    char type;
    bool ask_type = true;
    while (ask_type) /* User input sanitization. Essential in CLI based softwares.
                    Here the return value of scanf is bieng used. */
    {
        printf("Enter the type of account to be created : \n(I) Individual / (G) Group / (O) Organisation / (B) Business : ");
        if (scanf(" %c", &type) == 1) // true if user enters a char type
        {
            if (type == 'I' || type == 'G' || type == 'O' || type == 'B' || type == 'i' || type == 'g' || type == 'o' || type == 'b')
            {
                if (type > 95) // support in case user enters lowercase
                    type -= 32;
                new.type = type;
                ask_type = false;
            }
            else
            {
                printf("[INVALID TYPE, TRY AGAIN]\n"); // any other character
                while (getchar() != '\n')              // Clear buffer
                    ;
            }
        }
        else
        {
            printf("[INVALID TYPE, TRY AGAIN]\n");
            while (getchar() != '\n') // Clear buffer
                ;
        }
    }

    time_t t = time(NULL); /*sets current date-time using time.h module*/
    struct tm *tm = localtime(&t);
    new.creation_date = asctime(tm);

    printf("Enter Username : ");
    scanf(" %[^\n]s", new.name);

    if (new.type == 'I' || new.type == 'i') // taking DOB input
    {
        char bday_choice;
        printf("Do you want to set your birthday?(y/n) :");
        while (true)
        {
            if (scanf(" %c", &bday_choice) == 1)
            {
                if (bday_choice == 'y' || bday_choice == 'Y')
                {
                    new.dob_choice = true;
                    DOB_input_and_validity(new.dob);
                    break;
                }
                else if (bday_choice == 'n' || bday_choice == 'N')
                {
                    new.dob_choice = false;
                    break;
                }
                else
                {
                    printf("[INVALID RESPONSE, TRY AGAIN]\n");
                    printf("Do you want to set your birthday?(y/n) :");
                    while (getchar() != '\n')
                        ;
                }
            }
            else
            {
                printf("[INVALID RESPONSE, TRY AGAIN]\n");
                printf("Do you want to set your birthday?(y/n) :");
                while (getchar() != '\n')
                    ;
            }
        }
    }

    if (new.type == 'B' || new.type == 'O')
    {
        printf("Location will be needed\n");

        while (true)
        {

            double x;
            printf("coordinate X : ");
            if (scanf("%lf", &x) == 1)
            {
                new.loc.x = x;
                break;
            }
            else
            {
                printf("[INVALID LOCATION...TRY AGAIN]\n");

                while (getchar() != '\n')
                    ;
                continue;
            }
        }
        while (true)
        {

            double y;
            printf("coordinate Y : ");
            if (scanf("%lf", &y) == 1)
            {
                new.loc.y = y;
                break;
            }
            else
            {
                printf("[INVALID LOCATION...TRY AGAIN]\n");

                while (getchar() != '\n')
                    ;
                continue;
            }
        }
    }

    new.connections = NULL; // [IMPORTANT]!!
    new.posts = NULL;
    add_to_DB(&new);
    printf("\n[USER ACCOUNT CREATED!]  [USER ID : %d]\n", new.id);
}

void form_connections()
{
    int uid, target;
    bool to_connect = true;
    printf("Enter your UID-> \n");

    while (true)
    {
        if (scanf(" %d", &uid) == 1 && uid >= 0 && uid < DB_SIZE && USER_DB[uid].id != -1)
        {
            break;
        }
        else
        {
            printf("[INVALID UID...TRY AGAIN]\n");
            while (getchar() != '\n')
                ;
            printf("Enter your UID : ");
            while (getchar() != '\n')
                ;
        }
    }

    printf("Give a UID to connect to : ");
    while (true)
    {
        if (scanf(" %d", &target) == 1 && target >= 0 && target < DB_SIZE && USER_DB[target].id != -1)
        {
            break;
        }
        else
        {
            printf("[INVALID UID...TRY AGAIN]\n");
            printf("Enter your UID-> \n");
            while (getchar() != '\n')
                ;
        }
    }
    while (true)
    {
        if (connect(uid, target))
        {
            printf("[CONNECTED USER #%d and USER #%d]\n", uid, target);
            break;
        }
        else
        {
            char cont;
            printf("Do you want to try again? (y/n)\n");
            if (scanf(" %c", &cont) == 1)
            {
                if (cont == 'y' || cont == 'Y')
                {
                    while (getchar() != '\n')
                        ;
                    continue;
                }
                else if (cont == 'n' || cont == 'N')
                {
                    break;
                }
                else
                {
                    while (getchar() != '\n')
                        ;
                    continue;
                }
            }
            else
            {
                while (getchar() != '\n')
                    ;
                continue;
            }
        }
    }
}

void delete_user()
{
    int uid_to_delete;
    char final_choice;
    printf("Enter UID to delete : \n");
    while (true)
    {
        if (scanf(" %d", &uid_to_delete) == 1 && uid_to_delete >= 0 && uid_to_delete < DB_SIZE && USER_DB[uid_to_delete].id != -1)
        {
            break;
        }
        else
        {
            printf("[INVALID UID...TRY AGAIN]\n");
            printf("Enter your UID-> \n");
            while (getchar() != '\n')
                ;
        }
    }
    printf("Are you sure you want to delete an account?(y/n)\n");
    while (true)
    {
        if (scanf(" %c", &final_choice) == 1)
        {
            if (final_choice == 'y' || final_choice == 'Y')
                break;
            else
                return;
        }
        else
        {
            printf("[INVALID CHOICE...TRY AGAIN]\n");
            printf("Are you sure you want to delete an account?(y/n)\n");
            while (getchar() != '\n')
                ;
        }
    }

    if (final_choice == 'y' || final_choice == 'Y')
    {

        USER_DB[uid_to_delete].id = -1;

        for (int i = 0; i < DB_SIZE; i++)
        {
            if (USER_DB[i].id != -1)
            {
                delete_from_list(&(USER_DB[i].connections), uid_to_delete);
            }
        }
        for (int i = 0; i < POSTS_NUM; i++)
        {
            if (POSTS_DB[i].pid != -1)
            {
                delete_from_list(&(POSTS_DB[i].posters), uid_to_delete);
            }
        }
    }
    else
    {
        printf("[ABORTED]\n");
        return;
    }
    printf("[ACCOUNT DELETED]\n");
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------[SEARCH]--------------------------------------------------------------------

void search_user_by_filter()
{
    char filter;
    bool search = true;
    while (search)
    {
        printf("Which Parameter would you like to search with:\nName(n) /Birthday(b) /type(t) / <any other key to quit> : ");
        if (scanf(" %c", &filter) == 1)
        {
            if (filter == 'n' || filter == 'b' || filter == 't')
            {
                printf("==========================================================================================\n");
            }
            else
            {
                return;
            }
        }
        else
        {
            return;
        }

        if (filter == 'n')
        {
            char name_filter[100];
            printf("Enter the name you want to search by : \n");
            scanf(" %[^\n]s", name_filter);
            for (int i = 0; i < DB_SIZE; i++)
            {
                if (USER_DB[i].id != -1)
                {
                    if (strcmp(USER_DB[i].name, name_filter) == 0)
                    {
                        printf("[User #%d] | type: %c | name: %s\n", USER_DB[i].id, USER_DB[i].type, USER_DB[i].name);
                    }
                }
            }
            printf("=====================================[SEARCH COMPLETE]======================================\n\n");
        }
        else if (filter == 't')
        {
            char type_filter;
            printf("Enter the type you want to search by : \n");
            while (scanf(" %c", &type_filter) == 1)
            {
                if (type_filter == 'I' || type_filter == 'G' || type_filter == 'O' || type_filter == 'B' || type_filter == 'i' || type_filter == 'g' || type_filter == 'o' || type_filter == 'b')
                {
                    break;
                }
                else
                {
                    printf("[INVALID TYPE...TRY AGAIN]\n");
                    printf("Enter the type you want to search by : \n");
                    while (getchar() != '\n')
                        ;
                }
            }
            for (int i = 0; i < DB_SIZE; i++)
            {
                if (USER_DB[i].id != -1)
                {
                    if (USER_DB[i].type == type_filter)
                    {
                        printf("[User #%d] | type: %c | name: %s\n", USER_DB[i].id, USER_DB[i].type, USER_DB[i].name);
                    }
                }
            }
            printf("=====================================[SEARCH COMPLETE]======================================\n\n");
        }
        else if (filter == 'b')
        {
            char dob_filter[100];
            DOB_input_and_validity(dob_filter);

            for (int i = 0; i < DB_SIZE; i++)
            {
                if (USER_DB[i].id != -1 && USER_DB[i].type == 'I')
                {
                    if (strcmp(USER_DB[i].dob, dob_filter) == 0)
                    {
                        printf("[User #%d] | type: %c | name: %s | dob: %s\n", USER_DB[i].id, USER_DB[i].type, USER_DB[i].name, USER_DB[i].dob);
                    }
                }
            }
            printf("=====================================[SEARCH COMPLETE]======================================\n\n");
        }
        else
        {
            search = false;
        }
    }
    printf("[CLOSING SEARCH BAR]\n");
}

bool is_substring(char *s1, char *s2)
{
    int s1_len = strlen(s1);
    int s2_len = strlen(s2);

    for (int i = 0; i <= s2_len - s1_len; i++)
    {
        int j;
        for (j = 0; j < s1_len; j++)
            if (s2[i + j] != s1[j])
                break;

        if (j == s1_len)
            return true;
    }

    return false;
}

void post_search()
{
    char search[300];
    printf("Enter the content you would like to search: \n[RETURNS POSTS WHICH CONTAIN YOUR SEARCH AS A SUBSTRING]\n");
    scanf(" %[^\n]s", search);

    for (int i = 0; i < POSTS_NUM; i++)
    {
        if (is_substring(search, POSTS_DB[i].post))
        {
            printf("==========================================\n");
            printf("pid: %d | post: %s\n", POSTS_DB[i].pid, POSTS_DB[i].post);
        }
    }
    printf("==============================================\n");
    printf("[SEARCH COMPLETED]\n");
}

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------[DATA]--------------------------------------------------------------------

void individual_link_print()
{
    int uid;
    printf("Enter UID: \n");
    while (true)
    {
        if (scanf(" %d", &uid) == 1 && uid >= 0 && uid < DB_SIZE && USER_DB[uid].id != -1)
        {
            break;
        }
        else
        {
            printf("[INVALID UID...TRY AGAIN]\n");
            printf("Enter your UID-> \n");
            while (getchar() != '\n')
                ;
        }
    }

    conn_node *temp = USER_DB[uid].connections;
    if (temp == NULL)
    {
        printf("Empty connections!!\n");
        return;
    }

    while (temp)
    {
        if (USER_DB[temp->uid].type == 'G' || USER_DB[temp->uid].type == 'O')
        {
            conn_node *candidates = USER_DB[temp->uid].connections;
            while (candidates)
            {
                if (USER_DB[candidates->uid].type == 'I' && candidates->uid != uid)
                {
                    printf("[FOUND USER #%d,CONNECTED VIA USER#%d HERE ARE THEIR POSTS]\n", candidates->uid, temp->uid);
                    print_posts(&USER_DB[candidates->uid].posts);
                }
                candidates = candidates->next;
            }
        }
        (temp) = (temp)->next;
    }
    printf("[PRINTED LISTS]\n");
}

void print_1_hop()
{
    int uid;
    printf("Enter your UID\n");
    while (true)
    {
        if (scanf(" %d", &uid) == 1 && uid >= 0 && uid < DB_SIZE && USER_DB[uid].id != -1)
        {
            break;
        }
        else
        {
            printf("[INVALID UID...TRY AGAIN]\n");
            printf("Enter your UID-> \n");
            while (getchar() != '\n')
                ;
        }
    }

    if (&USER_DB[uid].connections)
    {
        printf("[LIST] : ");
        print_list(&USER_DB[uid].connections);
    }
    else
    {
        printf("[NO CONNECTIONS]\n");
    }
}

void print_DB()
{
    for (int i = 0; i < DB_SIZE; i++)
    {
        printf("\nPOS #%d : \n", i);
        if (USER_DB[i].id != -1)
        {
            printf("ID: %d\nName: %s\nCreated on: %s", USER_DB[i].id, USER_DB[i].name, USER_DB[i].creation_date);

            if (USER_DB[i].type == 'I')
            {
                printf("Type : Individual\n");
                if (USER_DB[i].dob_choice)
                {
                    printf("DOB : %s\n", USER_DB[i].dob);
                }
                else
                {
                    printf("DOB : Not supplied\n");
                }
            }
            if (USER_DB[i].type == 'B' || USER_DB[i].type == 'O')
            {
                if (USER_DB[i].type == 'B')
                {
                    printf("Type : Business\n");
                }
                if (USER_DB[i].type == 'O')
                {
                    printf("Type : Organisation\n");
                }

                printf("Location : (%.3lf, %.3lf)\n", USER_DB[i].loc.x, USER_DB[i].loc.y);
            }
            if (USER_DB[i].type == 'G')
            {
                printf("Type : Group\n");
            }
            printf("Connections : ");
            print_list(&USER_DB[i].connections);
            printf("Posts : ");
            print_posts(&USER_DB[i].posts);
        }
        else
        {
            printf("[EMPTY SLOT]\n");
        }
    }
}

void print_POSTS_DB()
{
    for (int i = 0; i < POSTS_NUM; i++)
    {
        printf("POST #%d : \n", i);
        if (POSTS_DB[i].pid != -1)
        {
            printf("pid: %d\ncontent: %s\n", POSTS_DB[i].pid, POSTS_DB[i].post);
            print_list(&POSTS_DB[i].posters);
        }
        else
        {
            printf("[EMPTY SLOT]\n");
        }
        printf("\n");
    }
}

void menu()
{
    bool menu_bool = true;
    int choice;
    while (menu_bool)
    {
        printf("\n==============================================[MENU]===========================================\n");
        printf("1. Create account\n2. Form Connections\n3. Delete account\n4. Search for an account\n5. Print all 1-hop linked nodes to an account\n6. Create a post\n7. Repost a post by post ID\n8. Search for content via substrings\n9. Display Content posted by an individual linked to another individual\n10. Print entire user database\n11. Print all the posts\n<-----------------------press 0 to quit------------------------>\n================================================================================================\n");
        printf("Enter choice : ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            create_user();
        }
        else if (choice == 2)
        {
            form_connections();
        }
        else if (choice == 3)
        {
            delete_user();
        }
        else if (choice == 4)
        {
            search_user_by_filter();
        }
        else if (choice == 5)
        {
            print_1_hop();
        }
        else if (choice == 6)
        {
            create_post();
        }
        else if (choice == 7)
        {
            repost();
        }
        else if (choice == 8)
        {
            post_search();
        }
        else if (choice == 9)
        {
            individual_link_print();
        }
        else if (choice == 10)
        {
            print_DB();
        }
        else if (choice == 11)
        {
            print_POSTS_DB();
        }
        else if (choice == 0)
        {
            menu_bool = false;
        }
        else
        {
            printf("[INVALID CHOICE, REDIRECTED TO MENU]\n");
            while (getchar() != '\n')
                ;
            continue;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
    init();
    init_posts();
    menu();

    return 0;
}