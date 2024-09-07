#include <iostream>
#include <fstream>
#include <string>

int records = 0;

class Child{
    std::string fname, lname, allergies, conditions, gender, preference;
    short int age;
    std::string contacts, emer_contacts, address;   
    //std::string curriculum[6];

protected:

public:

    Child(int dummy){}
    Child(){

        std::cout << "Enter details of the child:" << std::endl;

        std::cout << "Name first name: ";
        std::cin >> fname; 

        std::cout << "Name last name: ";
        std::cin >> lname; 

        while(1){
            std::cout << "Age: ";
            std::cin >> age; 
            if(age <= 15) break;
            else std::cout << "Can only accomodate children with age less than 16" << std::endl;
        }

        std::cout << "Gender: ";
        std::cin >> gender;

        std::cout << "Allergies (None if child has no allergies): ";
        std::cin >> allergies;

        std::cout << "Special Conditions (None if child has no conditions): ";
        std::cin >> conditions;  

        while(1){
            std::cout << "Parent/Gaurdian contact: ";
            std::cin >> contacts;
            if(all_of(contacts.begin(), contacts.end(), ::isdigit) && contacts.length() == 10) break;
            else std::cout << "Invalid Number" << std::endl;
        }

        while(1){
            std::cout << "Emergency contact: ";
            std::cin >>  emer_contacts;
            if(all_of(emer_contacts.begin(), emer_contacts.end(), ::isdigit) && emer_contacts.length() == 10) break;
            else std::cout << "Invalid Number" << std::endl;
        }
        curri();

        std::cout << "Enter food preference(Veg / Non-Veg ): ";
        std::cin >> preference;

        std::cout << std::endl;
    }
    
    void display(){
            std::cout << "Name: " << fname << " " <<  lname << std::endl;
            std::cout << "Age: " << age << std::endl;
            std::cout << "Gender: " << gender << std::endl;
            std::cout << "Allergies: " << allergies << std::endl;
            std::cout << "Conditions: " << conditions << std::endl;
            std::cout << "Parents/Gaurdian contact: " << contacts << std::endl;
            std::cout << "Emergency contact: " << contacts << std::endl;
            std::cout << std::endl;
        }

    void insert_record(){
            std::ofstream outFile("Kids", std::ios::out | std::ios::binary | std::ios::app);
            if(!outFile) std::cout << "Cannot open file." << std::endl;
            else{
            // write the private data members to the file as a single record
               outFile.write((char*)&(*this), sizeof(*this));
            }
            outFile.close();
        }

    void curri(){
        std::cout << "Cirriculum: " << std::endl;
        if(age <= 10){
            std::string curriculum[6] = {"Sub1: Circle time", "Sub2: Art", "Sub3: PE", "Sub4: Story time", "Sub5: Music and dance", "Sub6: Math"};
            for(int i=0; i<6; i++){
                std::cout << curriculum[i] << " ";
            }
            std::cout << std::endl;
        }
        else if(age >= 10){
            std::string curriculum[6] = {"Sub1: Language Arts", "Sub2: Math", "Sub3: Science", "Sub4: Social Studies", "Sub5: PE", "Sub6: Arts"};
            for(int i=0; i<6; i++){
                std::cout << curriculum[i] << " ";
            }
            std::cout << std::endl;
        }
    }

    friend void attendance();
    friend void breakfast(Child c);
    friend void lunch(Child c);
    friend void dinner(Child c);

};

/*void records(){
        Child temp = 1; //dummy
        std::fstream infile("Kids", std::ios::in | std::ios::binary);
        infile.read((char*)&temp, sizeof(temp));
        temp.display();
        infile.close();
}*/

void track_records(){
    Child temp = 1; 
    std::ifstream infile("Kids", std::ios::in | std::ios::binary);
    if(!infile){
        std::cout << "Cannot open file." << std::endl;
    }
    while(infile.read((char*)&temp, sizeof(temp))){
        records++;
    }
    infile.close();
}

void attendance(){
    track_records();
    std::string names[10];
    for(int i=0; i<records; i++){
        std::cout << "Enter student name: ";
        std::cin >> names[i];
    }

    Child temp = 1; 
    std::ifstream infile("Kids", std::ios::in | std::ios::binary);
    if(!infile){
        std::cout << "Cannot open file." << std::endl;
    }
    while(infile.read((char*)&temp, sizeof(temp))){
        int count = 0;
        for(int i=0; i<records; i++){
            if(temp.fname == names[i]){
                count ++;
            }
        }
        if(count == 0){
            std::cout << temp.fname << " is absent" << std::endl;
        }
    }
    infile.close();
}

void show_children(){
    Child temp = 1; 
    std::ifstream infile("Kids", std::ios::in | std::ios::binary);
    if(!infile){
        std::cout << "Cannot open file." << std::endl;
    }
    while(infile.read((char*)&temp, sizeof(temp))){
        temp.display();

        temp.curri();
        std::cout << std::endl;
        std::cout << "Food plan:" << std::endl;
        breakfast(temp);
        std::cout << std::endl;
        lunch(temp);
        std::cout << std::endl;
        dinner(temp);
        std::cout << std::endl;
    }
    infile.close();
}

void breakfast(Child c){
    std::cout << "Breakfast" << std::endl;
    if(c.allergies == "Peanut"  && c.preference == "Veg"){
        std::string food[7] = {"Upma", "Pongal", "Idli" , "Dosa", "Cereal", "Kichdi", "Bread"};
        std::string drink = "Milk(Boost/Horlicks/Complan)";
        std::cout << "Mon: " << food[0] << " Tue: " << food[1] << " Wed: " << food[2] << " Thurs: " << food[3] << " Fri: " << food[4] << " Sat: " << food[5] << " Sun: " << food[6] << std::endl;
        std::cout << "Drink: " << drink << std::endl;
    }

    else if(c.allergies == "Peanut" && c.preference == "Non-Veg"){
        std::string food[7] = {"Upma", "Pongal", "Idli" , "Egg Dosa", "Cereal", "Kichdi", "French toast"};
        std::string drink = "Milk(Boost/Horlicks/Complan)";
        std::cout << "Mon: " << food[0] << " Tue: " << food[1] << " Wed: " << food[2] << " Thurs: " << food[3] << " Fri: " << food[4] << " Sat: " << food[5] << " Sun: " << food[6] << std::endl;
        std::cout << "Drink: " << drink << std::endl;
    }

    else if(c.allergies == "Lactose" && c.preference == "Veg"){
        std::string food[7] = {"Upma", "Pongal", "Idli" , "Dosa", "Lentils", "Kichdi", "Chapathi"};
        std::string drink = "Fruit Juice(Orange/Apple/Watermelon)";
        std::cout << "Mon: " << food[0] << " Tue: " << food[1] << " Wed: " << food[2] << " Thurs: " << food[3] << " Fri: " << food[4] << " Sat: " << food[5] << " Sun: " << food[6] << std::endl;
        std::cout << "Drink: " << drink << std::endl;
    }

    else if(c.allergies == "Lactose" && c.preference == "Non-Veg"){
        std::string food[7]= {"Upma", "Pongal", "Idli" , "Egg Dosa", "Stuffed Egg", "Kichdi", "Chapathi"};
        std::string drink = "Fruit Juice(Orange/Apple/Watermelon)";
        std::cout << "Mon: " << food[0] << " Tue: " << food[1] << " Wed: " << food[2] << " Thurs: " << food[3] << " Fri: " << food[4] << " Sat: " << food[5] << " Sun: " << food[6] << std::endl;
        std::cout << "Drink: " << drink << std::endl;
    }

    else if(c.allergies == "None" && c.preference == "Veg"){
        std::string food[7] = {"Upma", "Pongal", "Idli" , "Dosa", "Cereal", "Kichdi", "Bread"};
        std::string drink = "Milk(Boost/Horlicks/Complan)";
        std::cout << "Mon: " << food[0] << " Tue: " << food[1] << " Wed: " << food[2] << " Thurs: " << food[3] << " Fri: " << food[4] << " Sat: " << food[5] << " Sun: " << food[6] << std::endl;
        std::cout << "Drink: " << drink << std::endl;
    }

    else if (c.allergies == "None" && c.preference == "Non-Veg") {
        std::string food[7] = {"Egg Bhurji", "Chicken Kebab", "Masala Omelette", "Fish Fry", "Poha", "Chhole Bhature", "Masala Dosa"};
        std::string drink = "Tea";
        std::cout << "Mon Breakfast: " << food[0] << " Tue Breakfast: " << food[1] << " Wed Breakfast: " << food[2] << " Thurs Breakfast: " << food[3] << " Fri Breakfast: " << food[4] << " Sat Breakfast: " << food[5] << " Sun Breakfast: " << food[6] << std::endl;
        std::cout << "Breakfast Drink: " << drink << std::endl;
    }
/////////////////////////////////////


}

void lunch(Child c){
    std::cout << "Lunch:" << std::endl;
    if(c.allergies == "Peanut"  && c.preference == "Veg"){
        std::string food[7] = {"Rice", "Sambhar", "Rasam" , "Curd rice", "Pasta", "Biryani", "Chole bhature"};
        std::string drink = "Buttermilk/Lemonade";
        std::cout << "Mon: " << food[0] << " Tue: " << food[1] << " Wed: " << food[2] << " Thurs: " << food[3] << " Fri: " << food[4] << " Sat: " << food[5] << " Sun: " << food[6] << std::endl;
        std::cout << "Drink: " << drink << std::endl;
    }

    else if(c.allergies == "Peanut" && c.preference == "Non-Veg"){
        std::string food[7] = {"Rice", "Sambhar", "Rasam" , "Curd rice", "Pasta", "Biryani", "Chicken biryani"};
        std::string drink = "Buttermilk/Lemonade";
        std::cout << "Mon: " << food[0] << " Tue: " << food[1] << " Wed: " << food[2] << " Thurs: " << food[3] << " Fri: " << food[4] << " Sat: " << food[5] << " Sun: " << food[6] << std::endl;
        std::cout << "Drink: " << drink << std::endl;
    }

    else if(c.allergies == "Lactose" && c.preference == "Veg"){
        std::string food[7] = {"Rice", "Sambhar", "Rasam" , "Vegetable curry", "Dal", "Biryani", "Roti with vegetable curry"};
        std::string drink = "Coconut water/Aam panna";
        std::cout << "Mon: " << food[0] << " Tue: " << food[1] << " Wed: " << food[2] << " Thurs: " << food[3] << " Fri: " << food[4] << " Sat: " << food[5] << " Sun: " << food[6] << std::endl;
        std::cout << "Drink: " << drink << std::endl;
    }

    else if(c.allergies == "Lactose" && c.preference == "Non-Veg"){
        std::string food[7]= {"Rice", "Sambhar", "Rasam" , "Egg curry", "Chicken curry", "Biryani", "Roti with chicken curry"};
        std::string drink = "Coconut water/Aam panna";
        std::cout << "Mon: " << food[0] << " Tue: " << food[1] << " Wed: " << food[2] << " Thurs: " << food[3] << " Fri: " << food[4] << " Sat: " << food[5] << " Sun: " << food[6] << std::endl;
        std::cout << "Drink: " << drink << std::endl;
    }

    else if(c.allergies == "None" && c.preference == "Veg"){
        std::string food[7] = {"Veg Pulao", "Rajma Masala", "Chole Bhature" , "Veg Biryani", "Paneer Tikka", "Mixed Veg Curry", "Dal Makhani"};
        std::string drink = "Lassi";
        std::cout << "Mon Lunch: " << food[0] << " Tue Lunch: " << food[1] << " Wed Lunch: " << food[2] << " Thurs Lunch: " << food[3] << " Fri Lunch: " << food[4] << " Sat Lunch: " << food[5] << " Sun Lunch: " << food[6] << std::endl;
        std::cout << "Lunch Drink: " << drink << std::endl;
    }

    else if(c.allergies == "None" && c.preference == "Non-Veg"){
        std::string food[7] = {"Chicken Biryani", "Fish Curry", "Egg Fried Rice" , "Mutton Curry", "Chicken Biriyani", "Prawn Fry", "Butter Chicken Masala"};
        std::string drink = "Lassi";
        std::cout << "Mon Lunch: " << food[0] << " Tue Lunch: " << food[1] << " Wed Lunch: " << food[2] << " Thurs Lunch: " << food[3] << " Fri Lunch: " << food[4] << " Sat Lunch: " << food[5] << " Sun Lunch: " << food[6] << std::endl;
        std::cout << "Lunch Drink: " << drink << std::endl;
    }


}

void dinner(Child c){
    std::cout << "Dinner" << std::endl;
    if(c.allergies == "Peanut" && c.preference == "Veg"){
        std::string food[7] = {"Roti", "Veg Pulao", "Chana Masala", "Dal Makhani", "Vegetable Fried Rice", "Vegetable Curry", "Veg Noodles"};
        std::string drink = "Buttermilk";
        std::cout << "Mon: " << food[0] << " Tue: " << food[1] << " Wed: " << food[2] << " Thurs: " << food[3] << " Fri: " << food[4] << " Sat: " << food[5] << " Sun: " << food[6] << std::endl;
        std::cout << "Drink: " << drink << std::endl;
    }

    else if(c.allergies == "Peanut" && c.preference == "Non-Veg"){
        std::string food[7] = {"Roti", "Chicken Biryani", "Chicken Curry", "Mutton Curry", "Egg Fried Rice", "Fish Fry", "Egg Noodles"};
        std::string drink = "Buttermilk";
        std::cout << "Mon: " << food[0] << " Tue: " << food[1] << " Wed: " << food[2] << " Thurs: " << food[3] << " Fri: " << food[4] << " Sat: " << food[5] << " Sun: " << food[6] << std::endl;
        std::cout << "Drink: " << drink << std::endl;
    }

    else if(c.allergies == "Lactose" && c.preference == "Veg"){
        std::string food[7] = {"Roti", "Veg Biryani", "Paneer Masala", "Dal Tadka", "Vegetable Fried Rice", "Vegetable Curry", "Veg Noodles"};
        std::string drink = "Water melon juice";
        std::cout << "Mon: " << food[0] << " Tue: " << food[1] << " Wed: " << food[2] << " Thurs: " << food[3] << " Fri: " << food[4] << " Sat: " << food[5] << " Sun: " << food[6] << std::endl;
        std::cout << "Drink: " << drink << std::endl;
    }

    else if(c.allergies == "Lactose" && c.preference == "Non-Veg"){
        std::string food[7]= {"Roti", "Chicken Biryani", "Chicken Curry", "Mutton Curry", "Egg Fried Rice", "Fish Fry", "Egg Noodles"};
        std::string drink = "Water melon juice";
        std::cout << "Mon: " << food[0] << " Tue: " << food[1] << " Wed: " << food[2] << " Thurs: " << food[3] << " Fri: " << food[4] << " Sat: " << food[5] << " Sun: " << food[6] << std::endl;
        std::cout << "Drink: " << drink << std::endl;
    }

    else if(c.allergies == "None" && c.preference == "Veg"){
        std::string food[7] = {"Veg Fried Rice", "Aloo Gobi", "Baingan Bharta" , "Palak Paneer", "Veg Korma", "Mushroom Masala", "Chana Masala"};
        std::string drink = "Buttermilk";
        std::cout << "Mon Dinner: " << food[0] << " Tue Dinner: " << food[1] << " Wed Dinner: " << food[2] << " Thurs Dinner: " << food[3] << " Fri Dinner: " << food[4] << " Sat Dinner: " << food[5] << " Sun Dinner: " << food[6] << std::endl;
        std::cout << "Dinner Drink: " << drink << std::endl;
    }

    else if(c.allergies == "None" && c.preference == "Non-Veg"){
        std::string food[7] = {"Chicken Tikka Masala", "Fish Curry", "Egg Masala" , "Mutton Rogan Josh", "Chicken Curry", "Prawn Masala", "Butter Chicken Masala"};
        std::string drink = "Buttermilk";
        std::cout << "Mon Dinner: " << food[0] << " Tue Dinner: " << food[1] << " Wed Dinner: " << food[2] << " Thurs Dinner: " << food[3] << " Fri Dinner: " << food[4] << " Sat Dinner: " << food[5] << " Sun Dinner: " << food[6] << std::endl;
        std::cout << "Dinner Drink: " << drink << std::endl;
    }

}



int main(){
    //Child a, b;
    //show_children();
    show_children();
    attendance();
}





