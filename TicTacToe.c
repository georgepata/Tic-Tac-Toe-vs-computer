#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int n;

void reload_board (char m[][10]){
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++) m[i][j]=' ';
}

void draw_board(char m[][10], int a, int b, char computer, char user, int ok){
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (i==a && j==b && ok) m[i][j]=computer;
            else if (i==a && j==b && ok==0) m[i][j]=user;
            printf("|  %c  ", m[i][j]);
            if (j==n-1) printf("|");
        }
        printf("\n");
        for (int k=0; k<=(n-1)*6+6; k++) printf("-");
        printf("\n");
    }
}

void instruction (){
    printf("\n");
    printf("Command 1: Level easy\n");
    printf("Command 2: Level medium\n");
    printf("Command 3: Level hard\n");
    printf("\n");
}

void gameplay (char m[][10], int a, int b, int ok, char computer, char user){
    if (ok) {
        m[a][b]=computer;
        draw_board(m,a,b,computer,user,ok);
    } else if (ok==0){
        m[a][b]=user;
        draw_board(m,a,b,computer,user,ok);
    }
}

int number_check(char m[][10], int a, int b){
    if (m[a][b]=='X' || m[a][b]=='0') return 1;
    return 0;
}

int winner (char m[][10], char computer, char user){
    int cntx,cnt0;
    for (int i=0; i<n; i++){
        cntx=0;cnt0=0;
        for (int j=0; j<n; j++){
            if (m[i][j]==computer) cntx++;
            else if (m[i][j]==user) cnt0++;
        }
        if (cntx==n && cntx!=0) return 1;
        else if (cnt0==n && cnt0!=0) return 2;
    }
    cntx=0; cnt0=0;
    for (int i=0; i<n; i++){
        cntx=0;cnt0=0;
        for (int j=0; j<n; j++){
            if (m[j][i]==computer) cntx++;
            else if (m[j][i]==user) cnt0++;
        }
        if (cntx==n && cntx!=0) return 1;
        else if (cnt0==n && cnt0!=0) return 2;
    }
    cntx=0; cnt0=0;
    for (int i=0; i<n; i++){
        if (m[i][i]==computer) cntx++;
        else if (m[i][i]==user) cnt0++;
    }
    if (cntx==n && cntx!=0) return 1;
        else if (cnt0==n && cnt0!=0) return 2;
    cntx=0; cnt0=0;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (i+j==n-1){
                if (m[i][j]==computer) cntx++;
                else if (m[i][j]==user) cnt0++;
            }
        }
    }
    if (cntx==n && cntx!=0) return 1;
    else if (cnt0==n && cnt0!=0) return 2;
    return 0;
}

void medium_level_computer (char m[][10], int aux1, int aux2, int *a, int *b, char computer, char user){
    printf("\n");
    int i,cnt=0,maxim1=0,maxim2=0,maxim3=0,coord1,coord2,ok;
    if (aux1==aux2){
        ok=1;
        for (i=0; i<n&&ok; i++){
            if (m[i][i]==user) ok=0;
            if (m[i][i]==computer) cnt++;
        }
        if (cnt > maxim1 && ok && cnt!=n) maxim1=cnt;
    }
    cnt=0; ok=1;
    for (i=0; i<n&&ok; i++){
        if (m[aux1][i]==user) ok=0;
        if (m[aux1][i]==computer) cnt++;
    }
    if (maxim2 < cnt && ok && cnt!=n) maxim2=cnt;
    cnt=0; ok=1;
    for (i=0; i<n&&ok; i++){
        if (m[i][aux2]==user) ok=0;
        if (m[i][aux2]==computer) cnt++;
    }
    if (maxim3 < cnt && ok && cnt!=n) maxim3=cnt;
    if (maxim1==0 && maxim2==0 && maxim3==0){
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++) if (m[i][j]==' ') {(*a)=i;(*b)=j;}
    }
    else if (maxim1>=maxim2 && maxim1>=maxim3){
        for (i=0; i<n; i++)
            if (m[i][i]==' ') {(*a)=i; (*b)=i;i=n;}
    } else if (maxim2>=maxim1 && maxim2>=maxim3) {
        for (i=0; i<n; i++)
            if (m[aux1][i]==' ') {(*a)=aux1; (*b)=i; i=n;}
    } else if (maxim3>=maxim1 && maxim3>=maxim1){
        for (i=0; i<n; i++)
            if (m[i][aux2]==' ') {(*a)=i; (*b)=aux2;i=n;}
    }
}

void hard_level_computer (char m[][10], int aux1, int aux2, int *a, int *b, char computer, char user){
    printf("\n");
    int i,cnt=0,maxim1=0,maxim2=0,maxim3=0,coord1,coord2,ok;
    if (aux1==aux2){
        ok=1;
        for (i=0; i<n&&ok; i++){
            if (m[i][i]==computer) ok=0;
            if (m[i][i]==user) cnt++;
        }
        if (cnt > maxim1 && ok && cnt!=n) maxim1=cnt;
    }
    cnt=0; ok=1;
    for (i=0; i<n&&ok; i++){
        if (m[aux1][i]==computer) ok=0;
        if (m[aux1][i]==user) cnt++;
    }
    if (maxim2 < cnt && ok && cnt!=n) maxim2=cnt;
    cnt=0; ok=1;
    for (i=0; i<n&&ok; i++){
        if (m[i][aux2]==computer) ok=0;
        if (m[i][aux2]==user) cnt++;
    }
    if (maxim3 < cnt && ok && cnt!=n) maxim3=cnt;
    if (maxim1==0 && maxim2==0 && maxim3==0){
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++) if (m[i][j]==' ') {(*a)=i;(*b)=j;}
    }
    else if (maxim1>=maxim2 && maxim1>=maxim3){
        for (i=0; i<n; i++)
            if (m[i][i]==' ') {(*a)=i; (*b)=i;i=n;}
    } else if (maxim2>=maxim1 && maxim2>=maxim3) {
        for (i=0; i<n; i++)
            if (m[aux1][i]==' ') {(*a)=aux1; (*b)=i; i=n;}
    } else if (maxim3>=maxim1 && maxim3>=maxim1){
        for (i=0; i<n; i++)
            if (m[i][aux2]==' ') {(*a)=i; (*b)=aux2;i=n;}
    } 
}

int main (){
    instruction();
    srand(time(0));
    int command,a=-1,b=-1,ok=1;
    char m[10][10],computer='X',user='0';
    printf("Choose number of lines and columns: ");
    scanf("%d", &n);
    reload_board (m);
    printf("\n\n");
    draw_board(m,a,b,computer,user,ok);
    printf("\n\n");
    printf("Choose your first command: ");
    scanf("%d",&command);
    printf("\n\n");
    int final=1; int cnt=0; int aux1; int aux2;
    int inceput=1;
    do{
        switch(command)
        {
            case 1:
                do{
                    if (ok){
                        printf("Computer's turn, choose a number between 0 and %d: ",n);
                        a=rand()%n;
                        b=rand()%n;
                        printf("%d %d", a, b);
                        if (number_check(m,a,b)==1){
                            while (number_check(m,a,b)==1){
                                a=rand()%n;
                                b=rand()%n;
                            }
                        }
                        printf("\n\n");
                        gameplay(m,a,b,ok,computer,user);
                        ok=0;
                    } else {
                        printf("User's turn, choose a number between 0 and %d: ",n);
                        scanf("%d%d",&a,&b);
                        if (number_check(m,a,b)==1){
                            while (number_check(m,a,b)==1){
                                printf("Choose a number between 0 and %d that is not taken: ", n);
                                scanf("%d%d", &a,&b);
                            }
                        }
                        printf("\n\n");
                        gameplay(m,a,b,ok,computer,user);
                        ok=1;
                        
                    }
                    printf("\n\n");
                    if (winner(m,computer,user)==1) {final=0;printf ("The winner is: %c\n\n", computer);}
                    else if (winner(m,computer,user)==2) {final=0;printf ("The winner is: %c\n\n", user);}
                    cnt++;
                    if (cnt==n*n-1) printf("Game has ended up in a tie!\n");
                } while (cnt!=n*n && final!=0);
                break;
            case 2:
                do{
                    if (inceput){
                        printf("Computer's turn, choose a number between 0 and %d: ",n);
                        a=rand()%n;
                        b=rand()%n;
                        printf("%d %d", a, b);
                        printf("\n\n");
                        inceput=0;
                        gameplay(m,a,b,ok,computer,user);
                        printf("\n\n");
                        ok=0;
                        aux1=a; aux2=b;
                    }
                    if (ok){
                        printf("Computer's turn, choose a number between 0 and %d: ",n);
                        medium_level_computer(m,aux1,aux2,&a,&b,computer,user);
                        printf("\n\n");
                        gameplay(m,a,b,ok,computer,user);
                        aux1=a; aux2=b;
                        ok=0;
                    } else if (ok==0){
                        printf("User's turn, choose a number between 0 and %d: ",n);
                        scanf("%d%d",&a,&b);
                        if (number_check(m,a,b)==1){
                            while (number_check(m,a,b)==1){
                                printf("Choose a number between 0 and %d that is not taken: ", n);
                                scanf("%d%d", &a,&b);
                            }
                        } 
                        printf("\n\n");
                        gameplay(m,a,b,ok,computer,user);
                        ok=1;
                    } 
                    printf("\n\n");
                    if (winner(m,computer,user)==1) {final=0;printf ("The winner is: %c\n\n", computer);}
                    else if (winner(m,computer,user)==2) {final=0;printf ("The winner is: %c\n\n", user);}
                    cnt++;
                    if (cnt==n*n-1) printf("Game has ended up in a tie!\n");
                } while (cnt!=n*n-1 && final!=0);
                break;
            case 3:
                do{
                    if (inceput){
                        printf("Computer's turn, choose a number between 0 and %d: ",n);
                        a=rand()%n; b=rand()%n;
                        printf("%d %d", a, b); printf("\n\n");
                        inceput=0;
                        gameplay(m,a,b,ok,computer,user);
                        printf("\n\n");
                        ok=0;
                    }
                    if (ok){
                        printf("Computer's turn, choose a number between 0 and %d: ",n);
                        hard_level_computer(m,aux1,aux2,&a,&b,computer,user);
                        printf("\n\n");
                        gameplay(m,a,b,ok,computer,user);
                        ok=0;
                    } else if (ok==0){
                        printf("User's turn, choose a number between 0 and %d: ",n);
                        scanf("%d%d",&a,&b);
                        if (number_check(m,a,b)==1){
                            while (number_check(m,a,b)==1){
                                printf("Choose a number between 0 and %d that is not taken: ", n);
                                scanf("%d%d", &a,&b);
                            }
                        } 
                        printf("\n\n");
                        gameplay(m,a,b,ok,computer,user);
                        ok=1;
                        aux1=a; aux2=b;
                    }
                    printf("\n\n");
                    if (winner(m,computer,user)==1) {final=0;printf ("The winner is: %c\n\n", computer);}
                    else if (winner(m,computer,user)==2) {final=0;printf ("The winner is: %c\n\n", user);}
                    cnt++;
                    if (cnt==n*n-1) printf("Game has ended up in a tie!\n");
                } while (cnt!=n*n-1 && final!=0);
                break;
        }
        instruction();
        printf("Choose another command: ");
        scanf("%d", &command);
        printf("\n\n");
        ok=1; final=1; cnt=0; inceput=1;
        reload_board(m);
    } while (command!=0); 
}