#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<conio.h>
#include<cstdlib>
using namespace std ;
int *curentdte() ;
class Produit{
	private:
		int  identifiant ;
		string nom ;
		string description ;
		double prix ;
		unsigned int quantite ;
	
	public :
		// constructeur
		Produit(int  identifiant=0 , string nom="" , string description="" , double prix=0.0  )
		{
			this->identifiant=identifiant;
			this->nom=nom;
			this->description=description;
			this->prix=prix;
			quantite=1;
		}
		
		// affichage
		void afficheProduit()
		{
			cout<<"   ID           : "<< identifiant<<endl ;
			cout<<"   Nom          : "<< nom <<endl;
			cout<<"   Description  : "<< description<<endl;
			cout<<"   Prix         : "<< prix <<endl;
			cout<<"   Quantite     : "<< quantite <<endl;
		}
		
		// saisie
		void saisieProduit(int id)
		{
			this->identifiant=identifiant;
			cout<<" ID           : " << identifiant << endl ;
			cout<<" Nom          : " ;
			cin>> nom ;
			cout<<" Description  : ";
			cin>> description;
			cout<<" Prix         : ";
			cin>> prix ; 
		}
		
		// getters
		int getID(){
			return identifiant;
		}
		double getPrix()
		{
			return prix ;
		}
		int getQuantite()
		{
			return quantite ;
		}
		// setters
		void setQuantite(unsigned int quantite)
		{
			this->quantite=quantite;
		}
		
};

class Client{
	private:
		int identifiant ;
		string nom ;
		string prenom ;
		string adresse ;
		int nbrfacture ; // nvl
	
	public :
		// constructeur
		Client()
		{
			nbrfacture=0;
		}
		
		//affichage
		void afficheClient()
		{
			cout<<"   Identifiant  : " << identifiant <<endl;
			cout<<"   Nom          : " << nom <<endl;
			cout<<"   Prenom       : "<< prenom<<endl;
			cout<<"   Adresse      : "<< adresse<<endl ;
		}
		
		//saisie
		void saisieClient(int identifiant)
		{
			this->identifiant=identifiant ;
			cout<<" ID           : " ;
			cout << identifiant << endl ;
			cout<<" Nom          : " ;
			cin>> nom ;
			cout<<" Prenom       : ";
			cin>> prenom;
			cout<<" Adresse      : ";
			cin>> adresse ;
		}
		//getters
		int getIdentifiant()
		{
			return identifiant;
		}
		int getNbrfacture()
		{
			return nbrfacture ;
		}
		//setters
		void setAdresse(string adresse)
		{
			this->adresse=adresse;
		}
		
		// nbr fct nvl
		void nvlfct()
		{
			nbrfacture++;
		}
		
};
class Facture{
	private:
		int code ;
		Client client ;
		vector<Produit> liste_produit ; 
		int *date ; 
		string etat ;
	
	public :
		//constructeur
		Facture()
		{
			etat="non payee";
		}
		
		//affichage
		void afficheFacture()
		{
			cout<<" Code : "<<code<<endl;
			cout<<" Client :"<< endl ;
			client.afficheClient();
			cout<<" Liste des produit :"<<endl;
			if(liste_produit.size()==0)
				cout<<"       ####### Pas de produit #######";
			else 
			{
				for(int i=0;i<liste_produit.size();i++)
				{
					liste_produit[i].afficheProduit();
				}
				cout << "********************************************************************"<<endl;
				cout<< " \t \t le montant : " << prixfacture()<<endl ;
			}
			cout<<" \t \t Date :"<<date[0]<<"/"<<date[1]<<"/"<<date[2]<<endl;
		}
		
		// saisie
		void saisieFacture(Client client ,int code )
		{
			this->code=code;
			cout<<"   Code de votre facture : "<<code<<endl;
			this->client=client;
			date=curentdte();
		}
		//verifier si un produit existe
		int produitexiste(Produit p)
		{
			for(int i=0;i<liste_produit.size();i++)
			{
				if(liste_produit[i].getID() == p.getID())
				return 1 ;
				
			}
			return 0 ;
		}
		// ajouter un produit a la facture
		void ajouterunproduit(Produit p)
		{
			if(produitexiste(p)==0)
				liste_produit.push_back(p);
			else 
				cout<<" -Produit existe deja";
		}
		// modifier la quantite d'un produit 
		void modifierunproduit(Produit p)
		{
			if(produitexiste(p)==1)
			{
				for(int i=0;i<liste_produit.size();++i)
				if(liste_produit[i].getID() == p.getID())
				{
					cout<<" - Entre la nouvelle quantite : ";
					unsigned int q ;
					cin>> q ;
					liste_produit[i].setQuantite(q);
				}
			}
			else 
				cout<<" - Produit n'existe pas deja : ";
		}

		// modifier les info d'un client -> const de copie 
		void modifierinfoclient()
		{
			cout << " - Entre la nouvelle adresse : ";
			string a ;
			cin >> a ;
			client.setAdresse(a);
		}
		// modifier le client de la facture
		void modifier_client_de_facture(Client client)
		{
			this->client=client;
		}

		// prix total d'une facture
		double prixfacture()
		{
			double t=0;
			for(int i=0;i<liste_produit.size();++i)
			{
				t+=liste_produit[i].getPrix() *liste_produit[i].getQuantite();
			}
			return t ;
		}

		// produit prix inf a donne
		void afficheproduitinf(double p)
		{
			int j=0;
			for(int i=0;i<liste_produit.size();++i)
			{
				if(liste_produit[i].getPrix() < p)
					liste_produit[i].afficheProduit();
				else j++ ;
			}
			if (liste_produit.size()==0)
			cout << " - Ya pas de produit "<<endl ;

			if(liste_produit.size()==j)
			cout << " - Ya pas de produit inferieure a "<< p <<endl ;
		}
		// supprimer un produit // 4h  supprimer un produit d'une facture
		void supprimerproduit(Produit p)
		{
			for(int i=0;i<liste_produit.size();++i)
			{
				if(liste_produit[i].getID() == p.getID())
				liste_produit.erase(liste_produit.begin()+i);
			}
		}
		// getters  
		int getCode()
		{
			return code ;
		}
		string getEtat()
		{
			return etat ;
		}
		Client getClient()
		{
			return client ;
		}
		int * getDate()
		{
			return date ;
		}
		//setters
		void setEtat(string etat)
		{
			this->etat=etat;
		}
		void setClient(Client client)
		{
			this->client=client;
		}
};

//tester si un client passe une facture
int testsiclientpassfact(Client c )
{
	if(c.getNbrfacture()==0)
		return 0 ; // pas de facture
	else return 1 ;
}
// teste si une fact aprt a un tableau
int testesiunefactaprtaatb(vector<Facture> tf , Facture f)
{
	for(int i=0;i<tf.size();++i)
	{
		if(tf[i].getCode() == f.getCode())
		return i ;
	}
	return -1 ;
}
// teste si une fact aprt a un tableau par code
int factaprtaatbpar_code(vector<Facture> tf , int code)
{
	for(int i=0;i<tf.size();++i)
	{
		if(tf[i].getCode() == code)
		return i ;
	}
	return -1 ;
}
// nvl // testes si un client existe deja
int testes_si_client_existe(vector<Client> client , int identifiant)
{
	for(int i=0;i<client.size();++i)
	{
		if(client[i].getIdentifiant()==identifiant)
		return i ;
	}
	return -1 ;
}
// nvl // Teste si un produit existe
int produitexiste(vector<Produit> produit ,int id)
{
	for(int i=0;i<produit.size();++i)
	if(produit[i].getID() == id)
	return i ;

	return -1 ;
}
// tester si un client passe une fact dans un tableau
int testesiclientpassfacttab(vector<Facture> tf,int identifiant)
{
	int j=-1 ;
	for(int i=0;i<tf.size();++i)
	{
		if(tf[i].getClient().getIdentifiant() == identifiant)
			return i; // client existe
	}
	return j ; // client napartient pas au tableau 
}
// modifier letat dune facture 
void modifieretatfacture(Facture f, string e)
{
	f.setEtat(e);
}
// ajouter une fact a un tableau 
void ajouter_fact_tableau(vector<Facture> tf , Facture f)
{
	tf.push_back(f);
}
// 4e  afficher les infos des fact du tableau 
void affiche_les_fact_tab(vector<Facture> tf)
{
	for(int i=0;i<tf.size();++i)
	{
		tf[i].afficheFacture();
	}
	if(tf.size() == 0)
	cout << " Ya pas de facture aujourd'hui "<< endl ;
}
// 4f  afficher les clients qui ont passe des factures sans paiment 
void affiche_fact_sans_paiment(vector<Facture> tf)
{
	for(int i=0;i<tf.size();++i)
	{
		if(tf[i].getEtat() == "non payee")
		tf[i].getClient().afficheClient();
	}
}
// 4g  modifier la quantite d'un produit dans une facture 
void modifier_quantite_facture(Facture tf , Produit p)
{
	tf.modifierunproduit(p);
}

// 4i  afficher les informations des facture qui one ete passe aujourd'hui
void affichfactaujourdhui(vector<Facture> tf)
{
	int *date;
	date=curentdte();
	for(int i=0;i<tf.size();++i)
	{
		int* datetf ;
		datetf=tf[i].getDate();
		if(date[0]==datetf[0] && date[1]==datetf[1] && date[2]==datetf[2])
		tf[i].afficheFacture();
	}
	if(tf.size() == 0)
	cout << " Ya pas de facture aujourd'hui "<< endl ;
}
// 4j  supprimer une facture d'un tableau
void supprimmerfacture(vector<Facture> &tf, int code)
{
	for(int i=0;i<tf.size();++i)
	{
		if(tf[i].getCode() == code)
		{
			tf.erase(tf.begin()+i);
			cout<< " Facture N"<<code<<"est supprimer "<<endl;
			break;
		}
	}
	
}
// nvl // affiche les produit 
void affichelesproduit(vector<Produit> produit)
{
	for(int i=0;i<produit.size();++i)
	{
		produit[i].afficheProduit();
	}
}

// return id produit
int idproduit()
{
	cout << "  - Entre l'id du produit :";
	int id ;
	cin >> id;
	return id ;
}
// return code facture
int codeFacture()
{
	cout << "  - Entre le code de la facture :";
	int code ;
	cin >> code ;
	return code ;
}
// return identifiant client
int identifiantclient()
{
	cout << "  - Entre l'identifiant du client :";
	int id ;
	cin >> id ;
	return id ;
}

// nvl //  rexupere la date actuelle du systeme
int *curentdte()
{
	// Get the current time
    time_t currentTime = time(NULL);
    // Convert the current time to a local time structure
    struct tm* localTime = localtime(&currentTime);
    // Extract day, month, and year from the local time structure
    int day = localTime->tm_mday;
    int month = localTime->tm_mon + 1;  // Note: Months are 0-indexed
    int year = localTime->tm_year + 1900;  // Years since 1900
    // Print the current date in the desired format
    //std::cout << "Current date: " << day << "-" << month << "-" << year << std::endl;
	static int date[3];
    date[0]=day;
    date[1]=month;
    date[2]=year ;
	return date ;
}


int main()
{
	int id;
	vector<Produit> produit ;
	
	do{
		id=(rand() % (999-100+1))+100 ;
	}while(produitexiste(produit ,id)!=-1);
	Produit p1(id , "wifi" , "description" , 123.3 );
	produit.push_back(p1);
	
	do{
		id=(rand() % (999-100+1))+100 ;
	}while(produitexiste(produit ,id)!=-1);
	Produit p2(id , "stylo" , "desc" , 4.5 );
	produit.push_back(p2);
	
	do{
		id=(rand() % (999-100+1))+100 ;
	}while(produitexiste(produit ,id)!=-1);
	Produit p3(id , "pain" , "desc" , 1.2);
	produit.push_back(p3);
	do{
		id=(rand() % (999-100+1))+100 ;
	}while(produitexiste(produit ,id)!=-1);
	Produit p4(id , "lait" , "desc" , 4.5 );
	produit.push_back(p4);
	
	int a ;
	int c ;
	int s ;
	vector<Client> client ;
	vector<Facture> facture ;
	vector<Facture> facturemodifier ;

	do{
		//menu principlae
		cout << " Tapez 1 pour la partie client "<< endl ;
		cout << " Tapez 2 pour la partie service "<< endl ;
		cout << " Tapez 0 pour quitter "<< endl ;
		cout<<endl<<"  Entre un chiffre : ";
		cin >> a ;
		system("cls");
		switch(a)
		{
			case 1 : // partie client
			{
				do
				{
					cout << " Tapez 1 pour s'inscrir "<< endl ;
					cout << " Tapez 2 pour une nvl facture " << endl ;
					cout << " Tapez 3 pour ajouter un produit a une facture "<< endl ;
					cout << " Tapez 4 pour le montant d'une facture "<< endl ;
					cout << " Tapez 5 pour payee une facture "<< endl ;
					cout << " Tapez 6 pour modifier une facture"<< endl ; // supprimer un produit et modifier la quantite d'un produit
					cout << " Tapez 7 pour modifier ladresse d'un client "<< endl ;
					cout << " Tapez 8 pour voir les informations personnelles "<< endl ;
					cout << " Tapez 9 pour voir les informations de la facture "<< endl ;
					cout << " Tapez 10 pour afficher les produit inferieure a un prix donne "<< endl ;
					cout << " Tapez 0 pour retourner au menu principale "<< endl ;

					cout<<endl<<"  Entre un chiffre : ";
					cin >> c ;

					switch(c)
					{
						case 0 : break;
						case 1 : //s'inscrir
							{
								Client c ;
								int id;
								do{
									id=(rand() % (99-10+1))+10 ;
								}while(testes_si_client_existe(client ,id)!=-1);
								c.saisieClient(id);
								if(testes_si_client_existe(client , c.getIdentifiant())==-1)
								client.push_back(c);
								else
								cout<<" 	client existe deja "<<endl ;
								break ;
							}
						case 2 : //une nvl facture
							{
								int j;
								j=testes_si_client_existe(client , identifiantclient());
								if(j!=-1)
								{
									Facture f;
									int id;
									do{
										id=(rand() % (99-10+1))+10 ;
									}while(factaprtaatbpar_code(facture , id)!=-1);
									f.saisieFacture(client[j],id);
									if(testesiunefactaprtaatb(facture ,f) == -1)
									facture.push_back(f);
									else 
									cout << " Facture existe deja " << endl ;
								}
								else cout<<" 	Client n'existe pas     "<<endl;
								break ;
							}
						case 3 : // ajouter un produit a une facture
							{
								int j=-1;
								string erreur=" Aucune";
								string pas ="";
								int code =codeFacture();
								for(int i=0;i<facture.size();++i)
								{
									erreur="";
									pas="pas";
									if(facture[i].getCode() == code)
									j=i;
								}
								if(j!=-1)
								{
									for(int i=0;i<produit.size();++i)
									produit[i].afficheProduit();
									
									int i=produitexiste(produit,idproduit());
									if(i!=-1)
									facture[j].ajouterunproduit(produit[i]);
									else cout << " Produit n'existe pas " << endl ;
								}
								else 
									cout << erreur << " Facture n'existe " << pas << endl ;
									
								break ;
							}
						case 4 : // calculer le prix d'une facture
							{
								int code=codeFacture();
								int i=factaprtaatbpar_code(facture,code);
								if(i!=-1)
								cout<< " Le prix de la facture N"<<code<<" est "<< facture[i].prixfacture()<< endl ;
								else cout << " Facture n'existe pas "<< endl;
								break ;	
							}
						case 5 : // payee une facture
							{
								int i=factaprtaatbpar_code(facture,codeFacture());
								if(i!=-1)
								{
									if(facture[i].getEtat() == "non payee" )
									{
										facture[i].setEtat("payee");
										facturemodifier.push_back(facture[i]);
										cout << " Facture payee "<<endl;
									}
									else 
									cout << " Facture deja payee " << endl ;
								}
								else cout << " Facture n'existe pas "<< endl;
								
								break ;
							}
						case 6 : // supprimer un produit et modifier la quantite d'un produit
							{
								cout << " Supprimer(S) ou modifier la quantite d'un produit(M) : ";
								char ms ;
								cin >> ms ;
								switch(ms)
								{
									case 'S' : // supprimer un produit de la facture 
										{
											int i=testes_si_client_existe(client,identifiantclient());
											if(i!=-1)
											{
												int code = codeFacture();
												for(int i=0;i<facture.size();++i)
												if(facture[i].getCode() == code)
												{
													int id=idproduit();
													for(int i=0;i<produit.size();++i)
													{
														if(produit[i].getID() == id)
														{
															facture[i].supprimerproduit(produit[i]);
															facturemodifier.push_back(facture[i]);
														}
													}
												}

											}
											else cout << " Veuillez s'inscrir "<<endl ;
											break ;
										}
									case 'M' : // modifier la quantite d'un produit
										{
											int i=factaprtaatbpar_code(facture,codeFacture());
											if(i!=-1)
											{
												int j=produitexiste(produit ,idproduit());
												if(j!=-1)
												{
													facture[i].modifierunproduit(produit[j]);
													facturemodifier.push_back(facture[i]);
												}
												else cout<<" Produit n'existe pas"<< endl;
											}
											else cout << " Facture n'existe pas "<< endl;
											break ;
										}
								}
								break;
							}
						case 7 : // modifier ladresse d'un client
						{
							int identifiant=identifiantclient();
							int i=testes_si_client_existe(client,identifiant);
							
							if(i!=-1)
							{
								string adresse;
								cout <<"  - Entre la nouvelle adresse : ";
								cin>> adresse ;
								client[i].setAdresse(adresse);
								int j=testesiclientpassfacttab(facture,identifiant);
								if(j!=-1)
								facture[j].setClient(client[i]);
								break;
							}
							else cout << " - Veuillez s'inscrir "<<endl ;
							
							break ;
						}
						case 8: //les informations personnelles
						{
							int i=testes_si_client_existe(client , identifiantclient());
							if(i!=-1)
							{
								client[i].afficheClient();
							}
							else cout << " - Veuillez s'inscrir "<<endl ;
							break ;
						}
						case 9 : // les informations de la facture
						{
							int i=factaprtaatbpar_code(facture,codeFacture());
							if(i!=-1)
							{
								facture[i].afficheFacture();
							}
							break ;
						}
						case 10 : // afficher les produit inferieure a un prix donne 
						{
							int code=codeFacture();
							int i=factaprtaatbpar_code(facture ,code);
							if(i!=-1)
							{
								cout << " - Afficher les produit inferieure a : ";
								double p ;
								cin >> p ;
								facture[i].afficheproduitinf( p);
							}
							else cout << " - Fcature n'existe pas "<< endl ;
							break ;
						}
						default : cout << "######## chiffre invalide ########" << endl ;
					}
					if(c!=0)
					{cout << " \t cliquer sur entrer " << endl ;
					getch();}
					system("cls");
				}while(c!=0);
				break ;
			}
			case 2 : // partie service
			{
				//service
                do{
                    cout << " Tapez 1 pour afficher les informations des facture qui one ete passe aujourd'hui"<< endl ;
                    cout << " Tapez 2 pour supprimer une facture d'un tableau"<< endl ;
                    cout << " Tapez 3 pour afficher les informations des factures du tableau "<< endl ;
                    cout << " Tapez 4 pour ajouter des produits"<< endl ;
                    cout << " Tapez 5 pour afficher les informations des clients"<< endl ;
                    cout << " Tapez 6 pour afficher les factures modifier"<< endl ;
                    cout << " Tapez 7 pour afficher les clients qui ont passe des factures sans paiment "<<endl;
                    cout << " Tapez 0 pour retourner au menu principale "<< endl ;
                    
                    cout<<endl<<"  Entre un chiffre : ";
                    cin >> s ;
                    switch(s)
                    {
						case 0 : break ;
                        case 1 : // afficher les informations des facture qui one ete passe aujourd'hui
                            {
                                affichfactaujourdhui(facture);
                                break ;
                            }
                        case 2 : // supprimer une facture d'un tableau
                            {
                                supprimmerfacture(facture, codeFacture());
                                break;
                            }
                        case 3 : // afficher les infos des factures du tableau
                            {
                                affiche_les_fact_tab(facture);
                                break ;
                            }
                        case 4 : // ajouter des produits
                            {
                                Produit p ;
								int id;
								do{
									id=(rand() % (999-100+1))+100 ;
								}while(produitexiste(produit ,id)!=-1);
                                p.saisieProduit(id);
                                produit.push_back(p);
                                break;
                            }
                        case 5 : // afficher les informations des clients
                            {
                                for(int i=0;i<client.size();++i)
                                client[i].afficheClient();
                                break;
                            }
                        case 6 : // afficher les factures modifier
                            {
                            	int cpt=0;
                                for(int i=0;i<facturemodifier.size();++i)
                                {
									facturemodifier[i].afficheFacture();
									cpt=1;
								}
								if(cpt==0)
								cout<<"y a pas de facture non payee"<<endl;
                                
                                break;
                            }
                        case 7 : // afficher les clients qui ont passe des factures sans paiment 
                            {
                            	cout<< "  les clients qui ont passe des factures sans paiment :"<<endl;
                            	vector<int> idclient;
								int cpt=0;
                                for(int i=0;i<facture.size();++i)
								{
									int test=0 ;
									for(int j=0;j<idclient.size();++j)
									if(facture[i].getClient().getIdentifiant() == idclient[j])
									test=1 ;
									
									if(facture[i].getEtat() == "non payee" && test == 0)
									{
										idclient.push_back(facture[i].getClient().getIdentifiant());
										facture[i].getClient().afficheClient();
										cpt=1;
									}
								}
								if(cpt == 0)
								cout << " Tous les factures sont payee "<< endl ;
								

								break;
                            }
						default : cout << "######## chiffre invalide ########" << endl ;
                    }
                    if(s!=0) 
					{cout << " \t cliquer sur entrer " << endl ;
					getch();}
                    system("cls");
                }while(s!=0);	
				break ;			
			}
			case 0 : // quitter
			{
				cout << " adios "<<endl ;
				break;
			}
			default : cout << "######## chiffre invalide ########" << endl ;
		}
		system("cls");
	}while(a!=0);
	return 0;
}	
