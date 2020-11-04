#include<fstream>
#include<string.h>
#include<iostream>
using namespace std;

class cd
{
    long p;
    char n[20],a[20],e[30];

    public:

    void create_contact()
    {
        cout<<"Phone: ";
        cin>>p;
        cout<<"Name: ";
        cin.ignore();
        cin>>n;
        cout<<"Address: ";
        cin.ignore();
        cin>>a;

        cout<<"Email address: ";
        cin.ignore();
        cin>>e;

        cout<<"\n";
    }

    void show_contact()
    {
        cout<<endl<<"Phone Number   #: "<<p;
        cout<<endl<<"Enter your Name: "<<n;
        cout<<endl<<"Address: "<<a;
        cout<<endl<<"Email Address : "<<e;
    }

    long getPhone()
    {
        return p;
    }

    char* getName()
    {
        return n;
    }

    char* getAddress()
    {
        return a;
    }

    char* getEmail()
    {
        return e;
    }
};

fstream fp;
cd cont;

void save_contact()
{
    fp.open("contactBook.txt",ios::out|ios::app);
    cont.create_contact();
    fp.write((char*)&cont,sizeof(cd));
    fp.close();
    cout<<endl<<endl<<"Contact is Created...";
    getchar();
}

void show_all_contacts()
{
    cout<<"\n\t\t================================\n\t\t\tAll COntacts\n\t \t================================\n";
    fp.open("contactBook.txt",ios::in);
    while(fp.read((char*)&cont,sizeof(cd)))
    {
        cont.show_contact();
        cout<<endl<<"=================================================\n"<<endl;
    }
    fp.close();
}
void display_contact(int num)
{
	bool found;
	int ch;

	found=false;
	fp.open("contactBook.txt",ios::in);
	while(fp.read((char*)&cont,sizeof(cd)))
	{
		if(cont.getPhone()==num)
		{
		cont.show_contact();
		found=true;
		}
	}
	fp.close();
	if(found == false){
	cout<<"\n\nNot found";}
	getchar();
}


void edit_contact()
{
    int num;
    bool found=false;

    cout<<"Edit contact\n===============================\n\n\t..::Enter the number of contact to edit:";
    cin>>num;
    fp.open("contactBook.txt",ios::in|ios::out);
    while(fp.read((char*)&cont,sizeof(cd)) && found==false)
    {
        if(cont.getPhone()==num)
        {
            cont.show_contact();
            cout<<"\nEnter THe new details "<<endl;
            cont.create_contact();
            int pos=-1*sizeof(cont);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&cont,sizeof(cont));
            cout<<endl<<endl<<"\t Saved";
            found=true;
        }
    }
    fp.close();
    if(found==false)
    cout<<endl<<endl<<"Not Found";
}

void delete_contact()
{
    int num;
    cout<<endl<<endl<<"Please Enter The contact #: ";
    cin>>num;
    fp.open("contactBook.txt",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.txt",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&cont,sizeof(cd)))
    {
        if(cont.getPhone()!=num)
        {
            fp2.write((char*)&cont,sizeof(cd));
        }
    }

}

int main(int argc, char *argv[])
{
    for(;;)
    {
        int ch;
        cout<<"\n\t **** Welcome to Contact Directory ****";
        cout<<"\n\n\n\t\t\tMAIN MENU\n\t\t=====================\n\t\t[1] Add a new Contact\n\t\t[2] List all Contacts\n\t\t[3] Search for contact\n\t\t[4] Edit a Contact\n\t\t[5] Delete a Contact\n\t\t[0] Exit\n\t\t=================\n\t\t";
        cout<<"Enter the choice:";
        cin>>ch;

        switch(ch)
        {
            case 0: cout<<"\n\n\t\tThank you for using CMS...";
                break;

            case 1:save_contact();
                break;

            case 2:show_all_contacts();
                break;
            case 3:
                int num;
                cout<<"\n\n\tPhone: ";
                cin>>num;
                display_contact(num);
                break;
            case 4:edit_contact();
                break;

            case 5:delete_contact();
                break;
            default:
                break;
        }

        int opt;
        cout<<"\n\n\n..::Enter the Choice:\n\n\t[1] Main Menu\t\t[0] Exit\n";
        cin>>opt;

        switch (opt)
        {
            case 1:
                continue;

            case 0:
                break;
        }
    }
    return 0;
}
