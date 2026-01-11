#include <iostream>
#include <string>


std::string sezar(std::string kaynak, char dondurme) {//Girilen stringi dondurme kadar döndürür.
	std::string yeni = "";
	for(int i = 0; i < kaynak.size();i++) {
		yeni.push_back(kaynak[i]+dondurme);
	}


	return yeni;


}



int main(int argc, char**argv) {

	if(argc != 4) {
		std::cout << "kullanım: <şifreleme> <kaynak dosya> <hedef dosya>\n";
	
	
		std::cout << "sezar ->" << sezar(std::string(argv[2]),atoi(argv[1])%255) << "\n";
	
	}







	return 0;

}
