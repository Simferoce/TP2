
#include "stdafx.h"
#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Platformer/Modele.h"
#include <vector>
#include "../Platformer/Controle.h"
//Il faut que ce dernier lien soit aussi dans 
//[right-click sur projet]\éditeur de liens\propriétés\entrées\dépendances additionnelles
//sinon il y aura une erreur de linkage

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjetSFMLTest
{		
	TEST_CLASS(ModeleTest)
	{
	public:
		
		TEST_METHOD(SplitValide)
		{
			std::string testString = "Allo:Allo2:Allo3";
			std::vector<std::string> splitted = Modele::split(testString, ':');
			Assert::IsTrue(splitted[0] == "Allo");
			Assert::IsTrue(splitted[1] == "Allo2");
			Assert::IsTrue(splitted[2] == "Allo3");
			Assert::IsTrue(splitted.size() == 3);
		}
		TEST_METHOD(SplitValideAvecVide)
		{
			std::string testString = "Allo::Allo2::";
			std::vector<std::string> splitted = Modele::split(testString, ':');
			Assert::IsTrue(splitted[0] == "Allo");
			Assert::IsTrue(splitted[1] == "");
			Assert::IsTrue(splitted[2] == "Allo2");
			Assert::IsTrue(splitted[3] == "");
			Assert::IsTrue(splitted[4] == "");
			Assert::IsTrue(splitted.size() == 5);
		}
		TEST_METHOD(SplitValideTotalVide)
		{
			std::string testString = "";
			std::vector<std::string> splitted = Modele::split(testString, ':');
			Assert::IsTrue(splitted[0] == "");
			Assert::IsTrue(splitted.size() == 1);
		}
		TEST_METHOD(SplitValideValideVise)
		{
			std::string testString = "Nickname:Password:Prenom:Nom:exemple@hotmail.com:101,1001,10001";
			std::vector<std::string> splitted = Modele::split(testString, ':');
			Assert::IsTrue(splitted[0] == "Nickname");
			Assert::IsTrue(splitted[1] == "Password");
			Assert::IsTrue(splitted[2] == "Prenom");
			Assert::IsTrue(splitted[3] == "Nom");
			Assert::IsTrue(splitted[4] == "exemple@hotmail.com");
			Assert::IsTrue(splitted[5] == "101,1001,10001");
			Assert::IsTrue(splitted.size() == 6);
		}
		TEST_METHOD(SplitValideValideViseAvecScore)
		{
			std::string testString = "Nickname:Password:Prenom:Nom:exemple@hotmail.com:101,1001,10001";
			std::vector<std::string> splitted = Modele::split(testString, ':');
			Assert::IsTrue(splitted[0] == "Nickname");
			Assert::IsTrue(splitted[1] == "Password");
			Assert::IsTrue(splitted[2] == "Prenom");
			Assert::IsTrue(splitted[3] == "Nom");
			Assert::IsTrue(splitted[4] == "exemple@hotmail.com");
			Assert::IsTrue(splitted[5] == "101,1001,10001");
			Assert::IsTrue(splitted.size() == 6);
			std::vector<std::string> score = Modele::split(splitted[5], ',');
			Assert::IsTrue(score[0] == "101");
			Assert::IsTrue(score[1] == "1001");
			Assert::IsTrue(score[2] == "10001");
			Assert::IsTrue(score.size() == 3);
		}
		TEST_METHOD(AuthentificationValide)
		{
			int emplacement = 0;
			Modele::ResultatAuthentification resulatAuthentification = Modele::AuthentifierUtilisateur("Nickname", "Password", emplacement, "..\\PlateformerTest\\sauvegardeTest.txt");
			Assert::IsTrue(resulatAuthentification == Modele::Reussi);
			Assert::IsTrue(emplacement == 0);
		}
		TEST_METHOD(AuthentificationNonPresentUtilisateur)
		{
			int emplacement = 0;
			Modele::ResultatAuthentification resulatAuthentification = Modele::AuthentifierUtilisateur("NicknameNonPresent", "Password", emplacement, "..\\PlateformerTest\\sauvegardeTest.txt");
			Assert::IsTrue(resulatAuthentification == Modele::Echouer);
			Assert::IsTrue(emplacement == -1);
		}
		TEST_METHOD(AuthentificationNonPresentMotPass)
		{
			int emplacement = 0;
			Modele::ResultatAuthentification resulatAuthentification = Modele::AuthentifierUtilisateur("Nickname", "PasswordNonPresent", emplacement, "..\\PlateformerTest\\sauvegardeTest.txt");
			Assert::IsTrue(resulatAuthentification == Modele::Echouer);
			Assert::IsTrue(emplacement == -1);
		}
		TEST_METHOD(AuthentificationAtreInfoAPlaceMotPass)
		{
			int emplacement = 0;
			Modele::ResultatAuthentification resulatAuthentification = Modele::AuthentifierUtilisateur("Nickname", "Prenom", emplacement, "..\\PlateformerTest\\sauvegardeTest.txt");
			Assert::IsTrue(resulatAuthentification == Modele::Echouer);
			Assert::IsTrue(emplacement == -1);
		}
		TEST_METHOD(AuthentificationValideAUneAutrePlaceQuAuDebut)
		{
			int emplacement = 0;
			Modele::ResultatAuthentification resulatAuthentification = Modele::AuthentifierUtilisateur("Nickname2", "Password2", emplacement, "..\\PlateformerTest\\sauvegardeTest.txt");
			Assert::IsTrue(resulatAuthentification == Modele::Reussi);
			Assert::IsTrue(emplacement == 1);
		}
		TEST_METHOD(AuthentificationMauvaisMotPassMaisPresentPourUnAutreUtilisateur)
		{
			int emplacement = 0;
			Modele::ResultatAuthentification resulatAuthentification = Modele::AuthentifierUtilisateur("Nickname", "Password2", emplacement, "..\\PlateformerTest\\sauvegardeTest.txt");
			Assert::IsTrue(resulatAuthentification == Modele::Echouer);
			Assert::IsTrue(emplacement == -1);
		}
		TEST_METHOD(UserExistValide)
		{
			int emplacement = 0;
			bool userExist = Controle::UserExist("Nickname", "..\\PlateformerTest\\sauvegardeTest.txt", emplacement);
			Assert::IsTrue(userExist);
			Assert::IsTrue(emplacement == 0);
		}
		TEST_METHOD(UserExistNonValide)
		{
			int emplacement = 0;
			bool userExist = Controle::UserExist("UtilisateurNonPresent", "..\\PlateformerTest\\sauvegardeTest.txt", emplacement);
			Assert::IsTrue(!userExist);
			Assert::IsTrue(emplacement == -1);
		}
		TEST_METHOD(UserExistUtilisantAutreInfo)
		{
			int emplacement = 0;
			bool userExist = Controle::UserExist("Password", "..\\PlateformerTest\\sauvegardeTest.txt", emplacement);
			Assert::IsTrue(!userExist);
			Assert::IsTrue(emplacement == -1);
		}
	};
	TEST_CLASS(ControleTest)
	{
	public:
		TEST_METHOD(AuthentificationValide)
		{
			int emplacement = 0;
			Modele::ResultatAuthentification resulatAuthentification = Controle::AuthentifierUtilisateur("Nickname", "Password", emplacement, "..\\PlateformerTest\\sauvegardeTest.txt");
			Assert::IsTrue(resulatAuthentification == Modele::Reussi);
			Assert::IsTrue(emplacement == 0);
		}
		TEST_METHOD(AuthentificationMotPassTropLong)
		{
			int emplacement = 0;
			Modele::ResultatAuthentification resulatAuthentification = Controle::AuthentifierUtilisateur("Nickname", "0123456789ABCDEF", emplacement, "..\\PlateformerTest\\sauvegardeTest.txt");
			Assert::IsTrue(resulatAuthentification == Modele::MotPassFormat);
			Assert::IsTrue(emplacement == -1);
		}
		TEST_METHOD(AuthentificationMotPassTropCourt)
		{
			int emplacement = 0;
			Modele::ResultatAuthentification resulatAuthentification = Controle::AuthentifierUtilisateur("Nickname", "0123", emplacement, "..\\PlateformerTest\\sauvegardeTest.txt");
			Assert::IsTrue(resulatAuthentification == Modele::MotPassFormat);
			Assert::IsTrue(emplacement == -1);
		}
		TEST_METHOD(AuthentificationNicknameTropLong)
		{
			int emplacement = 0;
			Modele::ResultatAuthentification resulatAuthentification = Controle::AuthentifierUtilisateur("0123456789ABCDEFGHIJKLMNOP", "Password", emplacement, "..\\PlateformerTest\\sauvegardeTest.txt");
			Assert::IsTrue(resulatAuthentification == Modele::UtilisateurFormat);
			Assert::IsTrue(emplacement == -1);
		}
		TEST_METHOD(AuthentificationNicknameTropCourt)
		{
			int emplacement = 0;
			Modele::ResultatAuthentification resulatAuthentification = Controle::AuthentifierUtilisateur("01", "Password", emplacement, "..\\PlateformerTest\\sauvegardeTest.txt");
			Assert::IsTrue(resulatAuthentification == Modele::UtilisateurFormat);
			Assert::IsTrue(emplacement == -1);
		}
		TEST_METHOD(AuthentificationNicknameMotPassLimiteCourt)
		{
			int emplacement = 0;
			Modele::ResultatAuthentification resulatAuthentification = Controle::AuthentifierUtilisateur("012", "01234", emplacement, "..\\PlateformerTest\\sauvegardeTest.txt");
			Assert::IsTrue(resulatAuthentification == Modele::Reussi);
			Assert::IsTrue(emplacement == 2);
		}
		TEST_METHOD(AuthentificationNicknameMotPassLimiteLong)
		{
			int emplacement = 0;
			Modele::ResultatAuthentification resulatAuthentification = Controle::AuthentifierUtilisateur("0123456789ABCDEFGHIJQLMNO", "0123456789ABCDE", emplacement, "..\\PlateformerTest\\sauvegardeTest.txt");
			Assert::IsTrue(resulatAuthentification == Modele::Reussi);
			Assert::IsTrue(emplacement == 3);
		}
		TEST_METHOD(UserExistNicknameTropLong)
		{
			int emplacement = 0;
			bool userExist = Controle::UserExist("0123456789ABCDEFGHIJKLMNOP", "..\\PlateformerTest\\sauvegardeTest.txt", emplacement);
			Assert::IsTrue(!userExist);
			Assert::IsTrue(emplacement == -1);
		}
		TEST_METHOD(UserExistNicknameTropCourt)
		{
			int emplacement = 0;
			bool userExist = Controle::UserExist("01", "..\\PlateformerTest\\sauvegardeTest.txt", emplacement);
			Assert::IsTrue(!userExist);
			Assert::IsTrue(emplacement == -1);
		}
	};
}