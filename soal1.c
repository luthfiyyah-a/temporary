#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <json-c/json.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

pid_t child_id;
int status;

void download(char* link)
{
    child_id = fork();

    if (child_id < 0) {
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
    }
    if (child_id == 0) 
    {
        printf("child PID = %d\n", getpid());
        char *argv[] = {"/usr/bin/wget", "-nd", link, NULL};
        execv("/usr/bin/wget", argv);
    }           
    while ((wait(&status)) > 0);
}

void ekstrak(char* file)
{
    child_id = fork();

    if (child_id < 0) {
        exit(EXIT_FAILURE);
    }
    if (child_id == 0) 
    {
        char *argv[] = {"/bin/unzip", file, NULL};
        execv("/bin/unzip", argv);
    } 
    while ((wait(&status)) > 0);
}

void buatFolder(char* nama)
{
    child_id = fork();

    if (child_id < 0) {
        exit(EXIT_FAILURE);
    }
    if (child_id == 0) 
    {
        char *argv[] = {"/usr/bin/mkdir", nama, NULL};
        execv("/usr/bin/mkdir", argv);
    } 
    while ((wait(&status)) > 0);
}

void pindahin(char* objek, char* tujuan)
{
    // memindahkan foder objek ke folder tujuan
    child_id = fork();
  
    if (child_id < 0) {
        exit(EXIT_FAILURE);
    }
    if (child_id == 0) 
    {
        char *argv[] = {"/usr/bin/mv", objek, tujuan, NULL};
        execv("/usr/bin/mv", argv);
    } 
    while ((wait(&status)) > 0);
}

int main(int argc)
{

    /* SOAL 1.a */ 
    char[] link_weapons = "https://drive.google.com/uc?id=1XSkAqqjkNmzZ0AdIZQt_eWGOZ0eJyNlT&export=download";
    char[] link_characters = "https://drive.google.com/uc?id=1xYYmsslb-9s8-4BDvosym7R4EmPi6BHp&export=download";
    char[] file_weapons = "uc?id=1XSkAqqjkNmzZ0AdIZQt_eWGOZ0eJyNlT&export=download";
    char[] file_characters = "uc?id=1xYYmsslb-9s8-4BDvosym7R4EmPi6BHp&export=download";

    download(link_weapons);
    ekstrak(file_weapons);
    download(link_characters);
    ekstrak(file_characters);

    buatFolder("gacha_gacha");

    // memindahkan weapons dan characters ke folder gacha_gacha
    pindahin("weapons", "gacha_gacha");
    pindahin("characters", "gacha_gacha");


    /* SOAL 1.b */ 
    int i = 0;
    int n = 270;
    time_t tes = ;
    int primogems = 79000;
    FILE *fp;
	char buffer[1024];
	struct json_object *parsed_json;
	struct json_object *name;
	struct json_object *rarity;

    while(primogems - 160 > 0)
    {   
        // setiap gacha menghabiskan 160 primogems
        primogems -= 160;

        printf("alhamdulillah %d\n", i);
        char nama_folder[100]; 
        char sjumlah[100];
        char nama_file[100];
        
        if(i%2 == 0)
        {
            // mengambil gacha item weapons jika genap
            printf("Enter path to list files: ");
            scanf("%s", path);

            dp = opendir(path);
            
            if (dp != NULL)
            {
                chdir("weapons");
                while ((ep = readdir (dp))) {
                    puts (ep->d_name);
                    fp = fopen(ep->d_name,"r");
                    fread(buffer, 10000, 1, fp);
                    fclose(fp);

                    parsed_json = json_tokener_parse(buffer);

                    json_object_object_get_ex(parsed_json, "name", &name);
                    json_object_object_get_ex(parsed_json, "rarity", &rarity);

                    printf("Name: %s\n", json_object_get_string(name));
                }

                (void) closedir (dp);
            } else perror ("Couldn't open the directory");
            printf("%d_weapons_%d_%s_%d", i, json_object_get_int(rarity), json_object_get_string(name), primogems);

            chdir("..");

        }
        else
        {
            // characters
        }

        if(i%90 == 0)
        {
            // membuat folder baru dengan format nama total_gacha_{jumlah-gacha}
            sprintf(sjumlah, "%d", i);
            strcpy(nama_folder, "total_gacha_");
            strcat(nama_folder, sjumlah);

            buatFolder(nama_folder);
        }


        if(i%10 == 0)
        {
            // char waktu = 
            strcpy(nama_file, "_gacha_");
            sprintf(sjumlah, "%d", i);    
            strcat(nama_file, sjumlah);

            // membuat file baru
            child_id = fork();
            if (child_id < 0) {
                exit(EXIT_FAILURE);
            }
            if (child_id == 0) 
            {                
                char *argv[] = {"touch", "folderku/fileku.txt", NULL};
                execv("/usr/bin/touch", argv);
            } 
            while ((wait(&status)) > 0);
        }

        i++;
    }

}