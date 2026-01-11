#include <iostream>

#include "httplib.h"
#include <filesystem>
#include <fstream>


std::string sezar(std::string a, char o) {
    std::string cikti ="";
    for(int i = 0; i < a.size();i++) {
        cikti.push_back((a[i])+o);
    }
    return cikti;
}
bool sayimi(std::string girdi) {
for(char c:girdi) {
if (!isdigit(c)) {
return false;
}
}

return true;
}


namespace fs = std::filesystem;
int main(int argc, char**argv) {
    httplib::Server server;
    server.Get(R"(/api/caesar/([^/]+)/(.+))", [](const httplib::Request& req, httplib::Response& res) {
        std::cout << req.path << " <-sezar("<<req.matches[1] << ")\n";
        std::string girdi = req.matches[2];
        std::string anahtar = req.matches[1];
        std::string body = sezar(girdi,std::stoi(anahtar) % 255);
        
        res.set_content(body, "text/plain");
    });

    server.Get(R"(/api/download/(.+))", [](const httplib::Request& req, httplib::Response& res) {
        std::cout << req.path << " <- dosya(indirme)\n";
            std::string directory = req.matches[1]; 
        std::cout << "istenen dosya: " << directory << "\n";


        if (fs::exists(directory) && fs::is_regular_file(directory)) {
            std::ifstream file(directory, std::ios::binary);
            std::string content((std::istreambuf_iterator<char>(file)),
                                (std::istreambuf_iterator<char>()));
            res.set_content(content, "application/octet-stream");
        } else {
            res.status = 404;
            res.set_content("File not found", "text/plain");
        }
    });
    server.Get(R"(/api/raw/(.+))", [](const httplib::Request& req, httplib::Response& res) {
        std::cout << req.path << " <- dosya(raw)\n";
            std::string directory = req.matches[1];
        std::cout << "istenen dosya: " << directory << "\n";

        if (fs::exists(directory) && fs::is_regular_file(directory)) {
            std::ifstream file(directory, std::ios::binary);
            std::string content((std::istreambuf_iterator<char>(file)),
                                (std::istreambuf_iterator<char>()));
            res.set_content(content, "text/plain");
        } else {
            res.status = 404;
            res.set_content("File not found", "text/plain");
        }
    });
   
    server.Get(R"(/favicon.ico)",[](const httplib::Request& req, httplib::Response& res){
	std::cout << req.path << " <- sayfa ikonu(tarayıcı olabilir)\n";

	if(fs::exists("./favicon.ico")) {
	    std::ifstream file("./favicon.ico",std::ios::binary);
	    std::string content((std::istreambuf_iterator<char>(file)),(std::istreambuf_iterator<char>()));

	    res.set_content(content,"image/x-icon");
	} else {
	    res.status = 404;
	    res.set_content("File not found", "text/plain");
	}
		    
		    
    });
	server.Get(R"(/api/rawcaesar/([^/]+)/(.+))", [](const httplib::Request& req, httplib::Response& res) {
			std::cout << req.path << "şifrelenmiş dosya(raw, sezar)\n";
			std::string directory = req.matches[2];
			int offset = std::stoi(req.matches[1]) % 255;
			std::cout << "istenen dosya: " << directory << "\n";
			if(fs::exists(directory) && fs::is_regular_file(directory)) {
			std::ifstream file(directory, std::ios::binary);
			std::string content((std::istreambuf_iterator<char>(file)),(std::istreambuf_iterator<char>()));
			res.set_content(sezar(content,offset),"text/plain");
			}		
	});
	server.Get(R"(/)", [](const httplib::Request& req, httplib::Response& res) {
		std::cout << req.path << " <- ana sayfa yükleme\n";
		std::ifstream file("index.html", std::ios::binary);
             	std::string content((std::istreambuf_iterator<char>(file)),(std::istreambuf_iterator<char>()));
        	res.set_content(content, "text/html");	     
	});



	server.set_error_handler([](const httplib::Request& req, httplib::Response& res){
	std::cout << req.path << " <- tanımlanmamış sayfa\n";
	res.status = 404;
	res.set_content("Aradığınız sayfa \"" +req.path +"\" bulunmamaktadir. <a href=\"/\">Ana Sayfaya don</a>","text/html");	
			
	});
	

	if(argv[1] != NULL) {
		std::cout << ((sayimi(argv[1])) ? "sayi:" : "sayidegil:")  << argv[1] << "\n";
	} else {
		std::cout << "argv[1] yok, port 8000 kullanılıyor.\n";
	}
    server.listen("0.0.0.0", (argv[1]==NULL||sayimi(argv[1]))?8000:std::stoi(argv[1]));
    return 0;
}
