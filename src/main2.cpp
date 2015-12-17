#include "parser_main.hpp"


//#include <Matrix>



int main(){

std::cout<<"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "<<std::endl;
std::cout<<"Ce programme permettra de réaliser des opérations floues sur une base de faits et une base de règles à l'aide d'un fuzzifier"<<std::endl;
std::cout<<"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "<<std::endl;


char* filename;
std::cout<<"Entrer le nom d'un fichier texte à analyser pour créer la base de faits"<<std::endl;
//std::cin>>filename;
//std::cout<<"Génération de la base de faits à base du fichier texte spécifié ... "<<std::endl;

//on parse les fichiers texte
std::vector<Fait> Faits = Parser_faits("faits.txt");

//on parse les regeles
std::vector<Rule> Rules = Parser_rules("rules.txt");


updateFaits(Faits, Rules);



//on créé nos vecteurs de valeur de fait
double listB[] = {0.001,0.005,0.005,0.01,0.1,0.3,0.4,0.6,0.8,0.9,1.0};
std::vector<double> uB (11);
std::vector<double> uTB(11);

uB[0]=0.001;
uB[1]=0.005;
uB[2]=0.005;
uB[3]=0.01;
uB[4]=0.1;
uB[5]=0.3;
uB[6]=0.4;
uB[7]=0.6;
uB[8]=0.8;
uB[9]=0.9;
uB[10]=1.0;


//it=uTB.begin(;)
for( std::vector<double>::iterator it = uB.begin() ; it != uB.end(); ++it){
	double value = *it;
	uTB.push_back(value*value);
	std::cout<<uTB.back()<<std::endl;
}

/*
std::tuple<std::string, std::string, double> line;
std::vector<std::tuple<std::string, std::string, double>> parsed_file;
 parsed_file.emplace_back("test","test",0);
std::cout<< std::get<0>(parsed_file[0]) << std::get<1>(parsed_file[0]) << std::get<2>(parsed_file[0]) << std::endl ;
*/


return 0;
}
