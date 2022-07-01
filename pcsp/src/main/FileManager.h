#pragma once
class FileManager 
{
   public:
    FileManager();
    FileManager(std::ifstream& f);
    void setActualFile(std::ifstream& f);
    void loadAndDefine(std::ifstream& f);
    std::ifstream& getActualFile();
    PBP &getPBP();

   private:
    void processPbp();

};
