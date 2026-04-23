#include <stdio.h>
void initializeGame(int game_board[2][7],int n){
    int i,j;
    for(i=0; i<2; i++){
        for(j=1;j<7;j++){
            game_board[i][j] = n;/*[1-6] aralığındaki kutuları n tane taş ile dolduruyorum,0 ları ise büyük küpler olarak seçtim onları 0 yapacağım*/
        }
    }
    game_board[0][0] = 0;/*0. sütun oyuncuya ait, ayrıca oyuncuyu diğer fonksiyonlarda da 0 ile temsil edeceğim bilgisayarı ise 1 ile.*/
    game_board[1][0] = 0;
}
void printBoard(int game_board[2][7]){
    int i,j;
    printf("+----+---+---+---+---+---+---+----+\n");
    printf("|    |%2d |%2d |%2d |%2d |%2d |%2d |    |\n",game_board[1][6],game_board[1][5],game_board[1][4],game_board[1][3],game_board[1][2],game_board[1][1]);/*üst tarafta bilgisayarın küpleri var*/
    printf("| %2d |---+---+---+---+---+---| %2d |\n",game_board[0][0],game_board[1][0]);/*sol tarafta oyuncunun büyük küpü var, sağ tarafta bilgisayarın büyük küpü var.*/
    printf("|    |%2d |%2d |%2d |%2d |%2d |%2d |    |\n",game_board[0][1],game_board[0][2],game_board[0][3],game_board[0][4],game_board[0][5],game_board[0][6]);/*alt tarafta oyuncunun küpleri var*/
    printf("+----+---+---+---+---+---+---+----+\n");
}
int move(int game_board[2][7],int choice, int flag, int last_player){
    /*flag = last_player = dağıtımın hangi tarafın küpünden başlayacağı(1 ise bilgisayara, 0 ise oyuncuya ait olan küplerden)
    flag fonksiyon içerisinde taşlar dağıtılırken değişecek ama last_player hep sabit kalacak. dağıtım sırası büyük küpe geldiğinde last_player = flag ise
    büyük küpe de taş konacak. değilse büyük küp esgeçilecek.*/
    /*choice = dağıtımın başlayacağı küpün numarısı*/
    int stones = game_board[flag][choice];
    game_board[flag][choice] = 0;
    for(stones;stones>0;stones--){
        choice++;/*başlangıç numarasından sonrakine geçiyoruz*/
        if(choice == 7){/*eğer yeni küp numarası 7 oldu ise flag'ı güncellemem ve ardından flag = last_player ise küp numarısını 0, değilse 1 yapmam gerekeir(büyük küpler 0 numaralı)*/
            flag++;
            flag%=2;
            if(last_player == flag){
                choice = 0;
            }
            else{
                choice = 1;
            }
        }
        game_board[flag][choice]++;/*yeni geçtiğimiz küpe taş koyma işlemi*/
    }
    if(choice == 0){
        return 0;/*dağıtım oyuncunun büyük küpünde bitti*/
    }
    else if(game_board[flag][choice] == 1){
        return 1;/*dağıtım boş küpte bitti(0'ken 1 oldu)*/
    }
    else{
        move(game_board,choice,flag,last_player);
    }
}
int gameplay(int game_board[2][7],int flag){
    /*flag sıranın kimde oldupunu temsil ediyor:0 ise oyuncuda 1 ise bilgisayarda*/
    int i,j,k;
    if(!flag){/*sıra oyuncuda ise bu if bloğu çalışır*/
        char entered_character;
        int choice;
        int last_cup;
        printf("Select a cup from ur side(enter a number in 1-6 interval):");
        scanf(" %c",&entered_character);/*input u karakter alarak alıp sonra sayıya çevireceğim.bu sayede geçersiz bir giriş yapılıp yapılmadığını kontrol edeceğim(ben sayı beklerken harf girilirse program hata vermeyecek)*/
        if(entered_character - '0' <= 0 || entered_character - '0' > 6){
            printf("%c is an invalid choose!\n",entered_character);
            gameplay(game_board,flag);
        }
        else{
            choice = entered_character - '0';/* yapılan geçerli girişi sayıya çevirme işlemi*/
        }
        if(game_board[flag][choice] != 0){/*seçilen küp boş değil bu blokta move() ile dağıtım yapılır*/
            last_cup = move(game_board,choice,flag,flag);
            printBoard(game_board);
            if(last_cup == 0){/*dağıtım oyuncunun büyük küpünde bitti*/
                printf("The distribution ended at your large cup,choose again!\n");
            }
            else{/*dağıtım boş bir küpte bitti*/
                printf("The distribution ended at an empty cup, its computer's turn!\n");
                flag++;
                flag%=2;
            }
        }
        else{
            printf("You can't select an empty cup!\n");/*boş bir küp seçildiyse fonksiyonun başa dönecek ve tekrar input bekleceyek*/
            gameplay(game_board,flag);
        }
    }
    else{/*sıra bilgisayarda ise bu blok çalışır*/
        int fake_board[2][7];/*game_boarda a eş olan sahte bir tahta oluşturup bu sahte tahta üzerinde move() ile denemeler yapacağım.*/
        int max = game_board[flag][0];
        int pc_choice = 8,pc_choice2 = 8;/*rastgele geçersiz bir tercih(8) atadım eğer aşağıdaki döngüde güncellenecek*/
        int dolu,large_cup;
        for(i=1;i<7;i++){
            if(game_board[flag][i] != 0){/*içerisinde 0 taş olan küpleri denemeye gerek yok*/
                dolu = i;
                for(k=0;k<2;k++){/*fake_board her move() sonrası değiştiğinden dolayı move() çağrılmadan önce her seferinde fake_board'ı game_board'a eşitliyorum*/
                    for(j=0;j<7;j++){
                        fake_board[k][j] = game_board[k][j];
                    }
                }
                large_cup = move(fake_board,i,flag,flag);/*sahte tahta üzerinde deneme işlemi*/
                if(fake_board[flag][0] > max){/*deneme sonucunda bilgisayarın büyük küpüne en çok taş koyan küp seçilir*/
                    pc_choice = i;
                    max = fake_board[flag][0];
                }
                if(large_cup == 0){
                    pc_choice2 = i;/*eğer pc_choice döngü sonunda güncellenemez ise ikincil tercih olarak dağıtımı büyük küpte bitiren bir küp varsa onu seçeceğim*/
                }
            }
        }
        if(pc_choice == 8){/*eğer pc_choice güncellenmedi ise hangi küp seçilirse seçilsin büyük küpe taş konamıyor demektir.*/
            if(pc_choice2 != 8){/*o zaman ikincil tercih büyük küpte bitiren küp olacak*/
                pc_choice = pc_choice2;
            }
            else{/*eğer hem büyük küpe taş koyan bir küp yok hemde dağıtımı büyük küpte bitiren bir küp yoksa dolu olan küplerden numarası büyük olan seçilir*/
                pc_choice = dolu;
            }
        }
        printf("computer's choice is:%d\n",pc_choice);
        int last_cup = move(game_board,pc_choice,flag,flag);/*sahte tahtada deneme işlemi bitti pc_choice belli oldu şimdi gerçek tahtada hamle yapma zamanı*/
        printBoard(game_board);
        if(last_cup == 0){/*dağıtım büyük küpte bitti sıra yine bilgisayarda*/
            printf("The distribution ended at computer's large cup, it will choose again!\n");
        }
        else{/*dağıtım boş küpte bitti flag ı güncellemek gerek*/
            printf("The distribution ended at an empty cup,its your turn!\n");
            flag++;
            flag%=2;
        }
    }
    for(i=0; i<2;i++){/*oyunun bitme koşulu bu iç içe for döngüsünde kontrol edilecek.*/
        for(j=1;j<7;j++){
            if(game_board[i][j] != 0){
                break;
            }
            if(j == 6){/*j değeri 6 olmuş ise iki taraftan bir tanesi boş demektir.skorları karşılaştırıp kazananınkini döndüreceğim.*/
                if(game_board[1][0] > game_board[0][0]){
                    printf("The winner is computer!\n");
                    return game_board[1][0];
                }
                else if(game_board[1][0] < game_board[0][0]){
                    printf("You win!\n");
                    return game_board[0][0];
                }
                else{
                    printf("its tie!\n");
                    return game_board[0][0];
                }
            }
        }
    }
    gameplay(game_board,flag);
}
int main(){
    int game_board[2][7];
    initializeGame(game_board,6);/*küçük küplerdeki taş sayısını 6 olarak ayarladım. eğer istenirse buradan 6 değeri yerine başka bir değer yazarak değiştirilebilir.*/
    printBoard(game_board);
    int winners_point = gameplay(game_board,0);
    printf("point:%d\n",winners_point);
    return 0;
}
