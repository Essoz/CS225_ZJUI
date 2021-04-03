#ifndef Define_h
#define Define_h

typedef struct 
{
    char name[10];
    char email[10];
    int  phone[10];
}Information;

enum Risk{
    no,low,medium,high
};

enum Profession{
    children,adolescent,youngadult,adult,senior,elderly,old
};

class Patient
{
private:
    int identificaiton;
    Risk risk;
    Profession profession;
    char name[10];
    char email[10];
    int  phone[10];
    int date;/*the format is YearMonthDate, Ex.20001204*/

public:
    Patient();
    Patient(int id,Profession prof,Risk risk,int date, Information info);
    ~Patient();

    /*set functions*/
    void setid(int id){
        identificaiton=id;
    };
    void setrisk(Risk R){
        risk=R;
    };
    void setprof(Profession prof){
        profession=prof;
    }
    void setinfo(Information info){
        name=info.name;
        
    }
    void setdate(int D){
        date=D;
    }
    /*get functions*/
    int getid(){
        return identificaiton;
    };
    Risk getrisk(){
        return risk;
    };
    Profession getprof(){
        return profession;
    }
    *Information getinfo(){
        return information;
        
    };
    int getdate(int D){
        return date;
    }
};
Patient::Patient(int id,Profession prof,Risk R,int D, Information info)
{
    setid(id);
    setprof(prof);
    setrisk(R);
    setdate(D);
    setinfo();
};





#endif /* Define_h */