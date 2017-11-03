
#include "stdafx.h"
#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Platformer/Modele.h"
#include <vector>
#include "../Platformer/Controle.h"
#include "../Platformer/SceneCreerCompte.h"
#include "../Platformer/Bloc.h"
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
		TEST_METHOD(GetTopTenResultAucunParametreSuplementaire)
		{
			std::vector<Modele::TopScore> topScoreTest = Modele::GetTopTenResult("..\\PlateformerTest\\sauvegardeTest.txt");
			Assert::IsTrue(topScoreTest[0].score == 9);
			Assert::IsTrue(topScoreTest[0].user == "Nickname");
			Assert::IsTrue(topScoreTest[1].score == 8);
			Assert::IsTrue(topScoreTest[1].user == "0123456789ABCDEFGHIJQLMNO");
			Assert::IsTrue(topScoreTest[2].score == 7);
			Assert::IsTrue(topScoreTest[2].user == "012");
			Assert::IsTrue(topScoreTest[3].score == 6);
			Assert::IsTrue(topScoreTest[3].user == "Nickname2");
			Assert::IsTrue(topScoreTest[4].score == 5);
			Assert::IsTrue(topScoreTest[4].user == "Nickname");
			Assert::IsTrue(topScoreTest[5].score == 4);
			Assert::IsTrue(topScoreTest[5].user == "0123456789ABCDEFGHIJQLMNO");
			Assert::IsTrue(topScoreTest[6].score == 3);
			Assert::IsTrue(topScoreTest[6].user == "012");
			Assert::IsTrue(topScoreTest[7].score == 2);
			Assert::IsTrue(topScoreTest[7].user == "Nickname2");
			Assert::IsTrue(topScoreTest[8].score == 1);
			Assert::IsTrue(topScoreTest[8].user == "Nickname");
			Assert::IsTrue(topScoreTest[9].score == 0);
			Assert::IsTrue(topScoreTest[9].user == "0123456789ABCDEFGHIJQLMNO");
			Assert::IsTrue(topScoreTest.size() == 10);
		}
		TEST_METHOD(GetTopTenResultAucunParametreSuplementaireSizePlusQue10)
		{
			std::vector<Modele::TopScore> topScoreTest = Modele::GetTopTenResult("..\\PlateformerTest\\sauvegardeScoreTest.txt");
			Assert::IsTrue(topScoreTest[0].score == 9);
			Assert::IsTrue(topScoreTest[0].user == "Nickname");
			Assert::IsTrue(topScoreTest[1].score == 8);
			Assert::IsTrue(topScoreTest[1].user == "Nickname");
			Assert::IsTrue(topScoreTest[2].score == 7);
			Assert::IsTrue(topScoreTest[2].user == "Nickname");
			Assert::IsTrue(topScoreTest[3].score == 6);
			Assert::IsTrue(topScoreTest[3].user == "Nickname");
			Assert::IsTrue(topScoreTest[4].score == 5);
			Assert::IsTrue(topScoreTest[4].user == "Nickname");
			Assert::IsTrue(topScoreTest[5].score == 4);
			Assert::IsTrue(topScoreTest[5].user == "Nickname");
			Assert::IsTrue(topScoreTest[6].score == 3);
			Assert::IsTrue(topScoreTest[6].user == "Nickname");
			Assert::IsTrue(topScoreTest[7].score == 2);
			Assert::IsTrue(topScoreTest[7].user == "Nickname");
			Assert::IsTrue(topScoreTest[8].score == 1);
			Assert::IsTrue(topScoreTest[8].user == "Nickname");
			Assert::IsTrue(topScoreTest[9].score == 0);
			Assert::IsTrue(topScoreTest[9].user == "Nickname");
			Assert::IsTrue(topScoreTest.size() == 10);
		}
		TEST_METHOD(GetTopTenResultAucunParametreSuplementaireSizeMoinsQue10)
		{
			std::vector<Modele::TopScore> topScoreTest = Modele::GetTopTenResult("..\\PlateformerTest\\sauvegardeScoreTest2.txt");
			Assert::IsTrue(topScoreTest[0].score == 9);
			Assert::IsTrue(topScoreTest[0].user == "Nickname");
			Assert::IsTrue(topScoreTest[1].score == 8);
			Assert::IsTrue(topScoreTest[1].user == "Nickname");
			Assert::IsTrue(topScoreTest[2].score == 7);
			Assert::IsTrue(topScoreTest[2].user == "Nickname");
			Assert::IsTrue(topScoreTest[3].score == 6);
			Assert::IsTrue(topScoreTest[3].user == "Nickname");
			Assert::IsTrue(topScoreTest[4].score == 5);
			Assert::IsTrue(topScoreTest[4].user == "Nickname");
			Assert::IsTrue(topScoreTest[5].score == 4);
			Assert::IsTrue(topScoreTest[5].user == "Nickname");
			Assert::IsTrue(topScoreTest[6].score == 3);
			Assert::IsTrue(topScoreTest[6].user == "Nickname");
			Assert::IsTrue(topScoreTest[7].score == 2);
			Assert::IsTrue(topScoreTest[7].user == "Nickname");
			Assert::IsTrue(topScoreTest[8].score == 1);
			Assert::IsTrue(topScoreTest[8].user == "Nickname");
			Assert::IsTrue(topScoreTest.size() == 9);
		}
		TEST_METHOD(GetTopTenResultAucunParametreSuplementaireAucunResultat)
		{
			std::vector<Modele::TopScore> topScoreTest = Modele::GetTopTenResult("..\\PlateformerTest\\sauvegardeScoreTest3.txt");
			Assert::IsTrue(topScoreTest.size() == 0);
		}
		TEST_METHOD(GetTopTenResultAucunParametreSuplementaireDuplicataScore)
		{
			std::vector<Modele::TopScore> topScoreTest = Modele::GetTopTenResult("..\\PlateformerTest\\sauvegardeScoreTest4.txt");
			Assert::IsTrue(topScoreTest[0].score == 9);
			Assert::IsTrue(topScoreTest[0].user == "Nickname2");
			Assert::IsTrue(topScoreTest[1].score == 9);
			Assert::IsTrue(topScoreTest[1].user == "Nickname2");
			Assert::IsTrue(topScoreTest[2].score == 9);
			Assert::IsTrue(topScoreTest[2].user == "Nickname2");
			Assert::IsTrue(topScoreTest[3].score == 9);
			Assert::IsTrue(topScoreTest[3].user == "Nickname2");
			Assert::IsTrue(topScoreTest[4].score == 9);
			Assert::IsTrue(topScoreTest[4].user == "Nickname2");
			Assert::IsTrue(topScoreTest[5].score == 9);
			Assert::IsTrue(topScoreTest[5].user == "Nickname");
			Assert::IsTrue(topScoreTest[6].score == 9);
			Assert::IsTrue(topScoreTest[6].user == "Nickname");
			Assert::IsTrue(topScoreTest[7].score == 9);
			Assert::IsTrue(topScoreTest[7].user == "Nickname");
			Assert::IsTrue(topScoreTest[8].score == 9);
			Assert::IsTrue(topScoreTest[8].user == "Nickname");
			Assert::IsTrue(topScoreTest[9].score == 9);
			Assert::IsTrue(topScoreTest[9].user == "Nickname");
			Assert::IsTrue(topScoreTest.size() == 10);
		}
		TEST_METHOD(GetTopTenResultScore)
		{
			std::vector<Modele::TopScore> topScoreTest = Modele::GetTopTenResult(9,"..\\PlateformerTest\\sauvegardeTest.txt");
			Assert::IsTrue(topScoreTest[0].score == 9);
			Assert::IsTrue(topScoreTest[0].user == "Nickname");
			Assert::IsTrue(topScoreTest.size() == 1);
		}
		TEST_METHOD(GetTopTenResultScoreSizePlusQue10)
		{
			std::vector<Modele::TopScore> topScoreTest = Modele::GetTopTenResult(0,"..\\PlateformerTest\\sauvegardeScoreTest5.txt");
			Assert::IsTrue(topScoreTest[0].score == 0);
			Assert::IsTrue(topScoreTest[0].user == "Nickname10");
			Assert::IsTrue(topScoreTest[1].score == 0);
			Assert::IsTrue(topScoreTest[1].user == "Nickname9");
			Assert::IsTrue(topScoreTest[2].score == 0);
			Assert::IsTrue(topScoreTest[2].user == "Nickname8");
			Assert::IsTrue(topScoreTest[3].score == 0);
			Assert::IsTrue(topScoreTest[3].user == "Nickname7");
			Assert::IsTrue(topScoreTest[4].score == 0);
			Assert::IsTrue(topScoreTest[4].user == "Nickname6");
			Assert::IsTrue(topScoreTest[5].score == 0);
			Assert::IsTrue(topScoreTest[5].user == "Nickname5");
			Assert::IsTrue(topScoreTest[6].score == 0);
			Assert::IsTrue(topScoreTest[6].user == "Nickname4");
			Assert::IsTrue(topScoreTest[7].score == 0);
			Assert::IsTrue(topScoreTest[7].user == "Nickname3");
			Assert::IsTrue(topScoreTest[8].score == 0);
			Assert::IsTrue(topScoreTest[8].user == "Nickname2");
			Assert::IsTrue(topScoreTest[9].score == 0);
			Assert::IsTrue(topScoreTest[9].user == "Nickname1");
			Assert::IsTrue(topScoreTest.size() == 10);
		}
		TEST_METHOD(GetTopTenResultScoreAucunResultat)
		{
			std::vector<Modele::TopScore> topScoreTest = Modele::GetTopTenResult(25, "..\\PlateformerTest\\sauvegardeTest.txt");
			Assert::IsTrue(topScoreTest.size() == 0);
		}
		TEST_METHOD(GetTopTenResultScoreDuplicataScore)
		{
			std::vector<Modele::TopScore> topScoreTest = Modele::GetTopTenResult(9,"..\\PlateformerTest\\sauvegardeScoreTest4.txt");
			Assert::IsTrue(topScoreTest[0].score == 9);
			Assert::IsTrue(topScoreTest[0].user == "Nickname2");
			Assert::IsTrue(topScoreTest[1].score == 9);
			Assert::IsTrue(topScoreTest[1].user == "Nickname2");
			Assert::IsTrue(topScoreTest[2].score == 9);
			Assert::IsTrue(topScoreTest[2].user == "Nickname2");
			Assert::IsTrue(topScoreTest[3].score == 9);
			Assert::IsTrue(topScoreTest[3].user == "Nickname2");
			Assert::IsTrue(topScoreTest[4].score == 9);
			Assert::IsTrue(topScoreTest[4].user == "Nickname2");
			Assert::IsTrue(topScoreTest[5].score == 9);
			Assert::IsTrue(topScoreTest[5].user == "Nickname");
			Assert::IsTrue(topScoreTest[6].score == 9);
			Assert::IsTrue(topScoreTest[6].user == "Nickname");
			Assert::IsTrue(topScoreTest[7].score == 9);
			Assert::IsTrue(topScoreTest[7].user == "Nickname");
			Assert::IsTrue(topScoreTest[8].score == 9);
			Assert::IsTrue(topScoreTest[8].user == "Nickname");
			Assert::IsTrue(topScoreTest[9].score == 9);
			Assert::IsTrue(topScoreTest[9].user == "Nickname");
			Assert::IsTrue(topScoreTest.size() == 10);
		}
		TEST_METHOD(GetTopTenResultUser)
		{
			std::vector<Modele::TopScore> topScoreTest = Modele::GetTopTenResult("Nickname", "..\\PlateformerTest\\sauvegardeTest.txt");
			Assert::IsTrue(topScoreTest[0].score == 9);
			Assert::IsTrue(topScoreTest[0].user == "Nickname");
			Assert::IsTrue(topScoreTest[1].score == 5);
			Assert::IsTrue(topScoreTest[1].user == "Nickname");
			Assert::IsTrue(topScoreTest[2].score == 1);
			Assert::IsTrue(topScoreTest[2].user == "Nickname");
			Assert::IsTrue(topScoreTest.size() == 3);
		}
		TEST_METHOD(GetTopTenResultUserSizePlusQue10)
		{
			std::vector<Modele::TopScore> topScoreTest = Modele::GetTopTenResult("Nickname", "..\\PlateformerTest\\sauvegardeScoreTest5.txt");
			Assert::IsTrue(topScoreTest[0].score == 10);
			Assert::IsTrue(topScoreTest[0].user == "Nickname");
			Assert::IsTrue(topScoreTest[1].score == 9);
			Assert::IsTrue(topScoreTest[1].user == "Nickname");
			Assert::IsTrue(topScoreTest[2].score == 8);
			Assert::IsTrue(topScoreTest[2].user == "Nickname");
			Assert::IsTrue(topScoreTest[3].score == 7);
			Assert::IsTrue(topScoreTest[3].user == "Nickname");
			Assert::IsTrue(topScoreTest[4].score == 6);
			Assert::IsTrue(topScoreTest[4].user == "Nickname");
			Assert::IsTrue(topScoreTest[5].score == 5);
			Assert::IsTrue(topScoreTest[5].user == "Nickname");
			Assert::IsTrue(topScoreTest[6].score == 4);
			Assert::IsTrue(topScoreTest[6].user == "Nickname");
			Assert::IsTrue(topScoreTest[7].score == 3);
			Assert::IsTrue(topScoreTest[7].user == "Nickname");
			Assert::IsTrue(topScoreTest[8].score == 2);
			Assert::IsTrue(topScoreTest[8].user == "Nickname");
			Assert::IsTrue(topScoreTest[9].score == 1);
			Assert::IsTrue(topScoreTest[9].user == "Nickname");
			Assert::IsTrue(topScoreTest.size() == 10);
		}
		TEST_METHOD(GetTopTenResultUserAucunResultat)
		{
			std::vector<Modele::TopScore> topScoreTest = Modele::GetTopTenResult("Jean-Claude", "..\\PlateformerTest\\sauvegardeTest.txt");
			Assert::IsTrue(topScoreTest.size() == 0);
		}
		TEST_METHOD(GetTopTenResultUserDuplicataScore)
		{
			std::vector<Modele::TopScore> topScoreTest = Modele::GetTopTenResult("Nickname", "..\\PlateformerTest\\sauvegardeScoreTest4.txt");
			Assert::IsTrue(topScoreTest[0].score == 9);
			Assert::IsTrue(topScoreTest[0].user == "Nickname");
			Assert::IsTrue(topScoreTest[1].score == 9);
			Assert::IsTrue(topScoreTest[1].user == "Nickname");
			Assert::IsTrue(topScoreTest[2].score == 9);
			Assert::IsTrue(topScoreTest[2].user == "Nickname");
			Assert::IsTrue(topScoreTest[3].score == 9);
			Assert::IsTrue(topScoreTest[3].user == "Nickname");
			Assert::IsTrue(topScoreTest[4].score == 9);
			Assert::IsTrue(topScoreTest[4].user == "Nickname");
			Assert::IsTrue(topScoreTest.size() == 5);
		}
		TEST_METHOD(GetTopTenResultUserScore)
		{
			std::vector<Modele::TopScore> topScoreTest = Modele::GetTopTenResult("Nickname", 9, "..\\PlateformerTest\\sauvegardeTest.txt");
			Assert::IsTrue(topScoreTest[0].score == 9);
			Assert::IsTrue(topScoreTest[0].user == "Nickname");
			Assert::IsTrue(topScoreTest.size() == 1);
		}
		TEST_METHOD(GetTopTenResultUserScoreSizePlusQue10)
		{
			std::vector<Modele::TopScore> topScoreTest = Modele::GetTopTenResult("Nickname",0, "..\\PlateformerTest\\sauvegardeScoreTest6.txt");
			Assert::IsTrue(topScoreTest[0].score == 0);
			Assert::IsTrue(topScoreTest[0].user == "Nickname");
			Assert::IsTrue(topScoreTest[1].score == 0);
			Assert::IsTrue(topScoreTest[1].user == "Nickname");
			Assert::IsTrue(topScoreTest[2].score == 0);
			Assert::IsTrue(topScoreTest[2].user == "Nickname");
			Assert::IsTrue(topScoreTest[3].score == 0);
			Assert::IsTrue(topScoreTest[3].user == "Nickname");
			Assert::IsTrue(topScoreTest[4].score == 0);
			Assert::IsTrue(topScoreTest[4].user == "Nickname");
			Assert::IsTrue(topScoreTest[5].score == 0);
			Assert::IsTrue(topScoreTest[5].user == "Nickname");
			Assert::IsTrue(topScoreTest[6].score == 0);
			Assert::IsTrue(topScoreTest[6].user == "Nickname");
			Assert::IsTrue(topScoreTest[7].score == 0);
			Assert::IsTrue(topScoreTest[7].user == "Nickname");
			Assert::IsTrue(topScoreTest[8].score == 0);
			Assert::IsTrue(topScoreTest[8].user == "Nickname");
			Assert::IsTrue(topScoreTest[9].score == 0);
			Assert::IsTrue(topScoreTest[9].user == "Nickname");
			Assert::IsTrue(topScoreTest.size() == 10);
		}
		TEST_METHOD(GetTopTenResultUserScoreAucunResultat)
		{
			std::vector<Modele::TopScore> topScoreTest = Modele::GetTopTenResult("Jean-Claude",-100, "..\\PlateformerTest\\sauvegardeTest.txt");
			Assert::IsTrue(topScoreTest.size() == 0);
		}
		TEST_METHOD(GetTopTenResultUserScoreDuplicataScore)
		{
			std::vector<Modele::TopScore> topScoreTest = Modele::GetTopTenResult("Nickname",9, "..\\PlateformerTest\\sauvegardeScoreTest4.txt");
			Assert::IsTrue(topScoreTest[0].score == 9);
			Assert::IsTrue(topScoreTest[0].user == "Nickname");
			Assert::IsTrue(topScoreTest[1].score == 9);
			Assert::IsTrue(topScoreTest[1].user == "Nickname");
			Assert::IsTrue(topScoreTest[2].score == 9);
			Assert::IsTrue(topScoreTest[2].user == "Nickname");
			Assert::IsTrue(topScoreTest[3].score == 9);
			Assert::IsTrue(topScoreTest[3].user == "Nickname");
			Assert::IsTrue(topScoreTest[4].score == 9);
			Assert::IsTrue(topScoreTest[4].user == "Nickname");
			Assert::IsTrue(topScoreTest.size() == 5);
		}
		TEST_METHOD(CreateNormalUser)
		{
			Assert::IsTrue(Modele::VerifierUtilisateur("allo"));
		}
		TEST_METHOD(CreateShorterUser)
		{
			Assert::IsFalse(Modele::VerifierUtilisateur("al"));
		}
		TEST_METHOD(CreateLongerUser)
		{
			Assert::IsFalse(Modele::VerifierUtilisateur("k3njfnvnrkrenfkdnvjfnvmfjvnf"));
		}
		TEST_METHOD(CreateNormalPassword)
		{
			Assert::IsTrue(Modele::VerifierMotDePasse("4rT)kj"));
		}
		TEST_METHOD(CreateShorterPassword)
		{
			Assert::IsFalse(Modele::VerifierMotDePasse("4T)k"));
		}
		TEST_METHOD(CreateLongerPassword)
		{
			Assert::IsFalse(Modele::VerifierMotDePasse("4T)kfkfdjfdjfdsjfdjfdsjfdsj"));
		}
		TEST_METHOD(CreateInvalidPassword)
		{
			Assert::IsFalse(Modele::VerifierMotDePasse("4*kn-k"));
		}
		TEST_METHOD(CreateNormalName)
		{
			Assert::IsTrue(Modele::VerifierNom("jon-phil.R"));
		}
		TEST_METHOD(CreateShortName)
		{
			Assert::IsFalse(Modele::VerifierNom("h"));
		}
		TEST_METHOD(CreateLongerName)
		{
			Assert::IsFalse(Modele::VerifierNom("hklklklklkokojojjojojojojojojoj"));
		}
		TEST_METHOD(CreateInvalidName)
		{
			Assert::IsFalse(Modele::VerifierNom("h*f+"));
		}
		TEST_METHOD(CreateValidEmail)
		{
			Assert::IsTrue(Modele::VerifierCourriel("jon@outlook.com"));
		}
		TEST_METHOD(CreateInvalidDomainEmail)
		{
			Assert::IsFalse(Modele::VerifierCourriel("jon@outlook.c"));
		}
		TEST_METHOD(CreateNoDomainEmail)
		{
			Assert::IsFalse(Modele::VerifierCourriel("jon@outlook"));
		}
		TEST_METHOD(CreateTooLongDomainEmail)
		{
			Assert::IsFalse(Modele::VerifierCourriel("jon@outlook.comm"));
		}
		TEST_METHOD(CreateDotAfterDomainEmail)
		{
			Assert::IsFalse(Modele::VerifierCourriel("jon@outlook.com."));
		}
		TEST_METHOD(CreateNoArobasEmail)
		{
			Assert::IsFalse(Modele::VerifierCourriel("jonoutlook.com"));
		}
		TEST_METHOD(CreateTwoArobasEmail)
		{
			Assert::IsFalse(Modele::VerifierCourriel("jon@out@look.com"));
		}
		TEST_METHOD(CreateSpecialCharEmail)
		{
			Assert::IsFalse(Modele::VerifierCourriel("jonéoutlook.com"));
		}
		TEST_METHOD(CreateNoSuffixEmail)
		{
			Assert::IsFalse(Modele::VerifierCourriel("jon@.com"));
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
	TEST_CLASS(Bloc)
	{
		TEST_METHOD(DetermineCollisionVector00None)
		{
			sf::Texture blocTexture;
			blocTexture.create(100, 100);
			platformer::Bloc testBloc(blocTexture);
			testBloc.setPosition(0, 0);

			FloatRect testOther(300,300,10,10);
			platformer::Bloc::Collision testCollision = testBloc.DetermineCollision(testOther, Vector2f(0, 0));
			Assert::IsTrue(testCollision == platformer::Bloc::Collision::None);
		}
		TEST_METHOD(DetermineCollisionVector10None)
		{
			sf::Texture blocTexture;
			blocTexture.create(100, 100);
			platformer::Bloc testBloc(blocTexture);
			testBloc.setPosition(0, 0);

			FloatRect testOther(300, 300, 10, 10);
			platformer::Bloc::Collision testCollision = testBloc.DetermineCollision(testOther, Vector2f(1, 0));
			Assert::IsTrue(testCollision == platformer::Bloc::Collision::None);
		}
		TEST_METHOD(DetermineCollisionVectorMinus10None)
		{
			sf::Texture blocTexture;
			blocTexture.create(100, 100);
			platformer::Bloc testBloc(blocTexture);
			testBloc.setPosition(0, 0);

			FloatRect testOther(300, 300, 10, 10);
			platformer::Bloc::Collision testCollision = testBloc.DetermineCollision(testOther, Vector2f(-1, 0));
			Assert::IsTrue(testCollision == platformer::Bloc::Collision::None);
		}
		TEST_METHOD(DetermineCollisionVector01None)
		{
			sf::Texture blocTexture;
			blocTexture.create(100, 100);
			platformer::Bloc testBloc(blocTexture);
			testBloc.setPosition(0, 0);

			FloatRect testOther(300, 300, 10, 10);
			platformer::Bloc::Collision testCollision = testBloc.DetermineCollision(testOther, Vector2f(0, 1));
			Assert::IsTrue(testCollision == platformer::Bloc::Collision::None);
		}
		TEST_METHOD(DetermineCollisionVector0Minus1None)
		{
			sf::Texture blocTexture;
			blocTexture.create(100, 100);
			platformer::Bloc testBloc(blocTexture);
			testBloc.setPosition(0, 0);

			FloatRect testOther(300, 300, 10, 10);
			platformer::Bloc::Collision testCollision = testBloc.DetermineCollision(testOther, Vector2f(0, -1));
			Assert::IsTrue(testCollision == platformer::Bloc::Collision::None);
		}
		TEST_METHOD(DetermineCollisionVector11None)
		{
			sf::Texture blocTexture;
			blocTexture.create(100, 100);
			platformer::Bloc testBloc(blocTexture);
			testBloc.setPosition(0, 0);

			FloatRect testOther(300, 300, 10, 10);
			platformer::Bloc::Collision testCollision = testBloc.DetermineCollision(testOther, Vector2f(1, 1));
			Assert::IsTrue(testCollision == platformer::Bloc::Collision::None);
		}
		TEST_METHOD(DetermineCollisionVectorMinus1Minus1None)
		{
			sf::Texture blocTexture;
			blocTexture.create(100, 100);
			platformer::Bloc testBloc(blocTexture);
			testBloc.setPosition(0, 0);

			FloatRect testOther(300, 300, 10, 10);
			platformer::Bloc::Collision testCollision = testBloc.DetermineCollision(testOther, Vector2f(-1, -1));
			Assert::IsTrue(testCollision == platformer::Bloc::Collision::None);
		}
		TEST_METHOD(DetermineCollisionVector00NoSide)
		{
			sf::Texture blocTexture;
			blocTexture.create(100, 100);
			platformer::Bloc testBloc(blocTexture);
			testBloc.setPosition(0, 0);

			FloatRect testOther(50, 50, 10, 10);
			platformer::Bloc::Collision testCollision = testBloc.DetermineCollision(testOther, Vector2f(0, 0));
			Assert::IsTrue(testCollision == platformer::Bloc::Collision::CollisionWithNoDeterminateSide);
		}
		TEST_METHOD(DetermineCollisionVector10Left)
		{
			sf::Texture blocTexture;
			blocTexture.create(100, 100);
			platformer::Bloc testBloc(blocTexture);
			testBloc.setPosition(0, 0);

			FloatRect testOther(0, 0, 10, 10);
			platformer::Bloc::Collision testCollision = testBloc.DetermineCollision(testOther, Vector2f(1, 0));
			Assert::IsTrue(testCollision == platformer::Bloc::Collision::Left);
		}
		TEST_METHOD(DetermineCollisionVectorMinus10Right)
		{
			sf::Texture blocTexture;
			blocTexture.create(100, 100);
			platformer::Bloc testBloc(blocTexture);
			testBloc.setPosition(0, 0);

			FloatRect testOther(0, 0, 10, 10);
			platformer::Bloc::Collision testCollision = testBloc.DetermineCollision(testOther, Vector2f(-1, 0));
			Assert::IsTrue(testCollision == platformer::Bloc::Collision::Right);
		}
		TEST_METHOD(DetermineCollisionVector01Top)
		{
			sf::Texture blocTexture;
			blocTexture.create(100, 100);
			platformer::Bloc testBloc(blocTexture);
			testBloc.setPosition(0, 0);

			FloatRect testOther(0, 0, 10, 10);
			platformer::Bloc::Collision testCollision = testBloc.DetermineCollision(testOther, Vector2f(0, 1));
			Assert::IsTrue(testCollision == platformer::Bloc::Collision::Top);
		}
		TEST_METHOD(DetermineCollisionVector0Minus1Bot)
		{
			sf::Texture blocTexture;
			blocTexture.create(100, 100);
			platformer::Bloc testBloc(blocTexture);
			testBloc.setPosition(0, 0);

			FloatRect testOther(0, 0, 10, 10);
			platformer::Bloc::Collision testCollision = testBloc.DetermineCollision(testOther, Vector2f(0, -1));
			Assert::IsTrue(testCollision == platformer::Bloc::Collision::Bot);
		}
		TEST_METHOD(DetermineCollisionVector11PriorityTop)
		{
			sf::Texture blocTexture;
			blocTexture.create(100, 100);
			platformer::Bloc testBloc(blocTexture);
			testBloc.setPosition(0, 0);

			FloatRect testOther(45, 45, 10, 10);
			platformer::Bloc::Collision testCollision = testBloc.DetermineCollision(testOther, Vector2f(1, 1));
			Assert::IsTrue(testCollision == platformer::Bloc::Collision::Top);
		}
		TEST_METHOD(DetermineCollisionVector11PriorityBot)
		{
			sf::Texture blocTexture;
			blocTexture.create(100, 100);
			platformer::Bloc testBloc(blocTexture);
			testBloc.setPosition(0, 0);

			FloatRect testOther(45, 45, 10, 10);
			platformer::Bloc::Collision testCollision = testBloc.DetermineCollision(testOther, Vector2f(1, -1));
			Assert::IsTrue(testCollision == platformer::Bloc::Collision::Bot);
		}
		TEST_METHOD(DetermineCollisionVector001Top)
		{
			sf::Texture blocTexture;
			blocTexture.create(100, 100);
			platformer::Bloc testBloc(blocTexture);
			testBloc.setPosition(99, 99);

			FloatRect testOther(0,0,200,200);
			platformer::Bloc::Collision testCollision = testBloc.DetermineCollision(testOther, Vector2f(0, 0.1));
			Assert::IsTrue(testCollision == platformer::Bloc::Collision::Top);
		}
	};

}