#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include <vector>
#include <random>
//trouve le caractere ':' dans le texte
//on considere qu'il y a des espaces autour de ':'
int find_char(std::string s){
    int l = s.length();
    int ind =-1;
    for (int i =0; i<l; i++){
        if (s[i]==':'){
            ind = i;
        }
    }
    return ind;
}

std::vector<std::string> lecture() {
    std::vector<std::string> t;
    std::string nomFichier = "voc_insurance.txt";

    std::ifstream fichier(nomFichier);


    if (!fichier.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
    }

    std::string ligne;
    while (std::getline(fichier, ligne)) {
        t.push_back(ligne);
    }

    fichier.close();
    return t;
}
bool a_question(std::string fr, std::string en){
    std::cout<<fr<<std::endl;
    std::string answer;
    std::getline(std::cin, answer);
    if (answer==en){
        std::cout<< "good answer"<<std::endl;
    }else{
        std::cout<<answer.length()<<" false, it was :"<<en<<std::endl;
    }
    return (answer == en);

}

int voc_test(std::vector<std::string> liste){
    int good_answer = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 129);
    for (int i=0; i<5; i++){ // nombre de questions
        int j = distribution(gen);
        int ind = find_char(liste[j]);
        if (ind == -1){
            std::cout << "erreur"<<std::endl;
            return 0;

        }else{
            liste[j][ind-1]='\0'; // attention cela marche parce que je sais qu'il y a des espaces autour de :
            std::string fr = &liste[j][0];
            std::string en = &liste[j][ind+2];
            if (a_question(fr, en)){
                good_answer ++;
            }
        }
    }
    std::cout<<"your score is "<<good_answer<<"/5 \n"<< std::endl;  
    return 0;
}

bool start(){
    std::cout<<"do you want to pass a vocabulary test? (yes or no), it's 10 question"<<std::endl;
    std::string ans;
    std::getline(std::cin, ans);   
    if (ans!="no"&& ans!="yes"){
        std::cout<<"answer the question: ";
        return start();
    }else{
        if (ans == "no"){
        return false;
        }
        if (ans == "yes"){
            return true;
        }
    }    
}

void interaction(){
    std::vector<std::string> t;
    t = lecture();
    while(true){
        if (start()){
            std::cout<< "lancement du test: \n  "<<std::endl;
            voc_test(t);
        }else{
            std::cout<<"bye bye "<<std::endl; 
            return ;
        }
    }
}


int main(){
    interaction();
    return 0;
}