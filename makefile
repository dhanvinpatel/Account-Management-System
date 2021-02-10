account_system: main.o menu.o account.o account_settings.o bank_account.o stock_account.o
	g++ main.o menu.o account.o account_settings.o bank_account.o stock_account.o -o account_system

main.o: main.cpp
	g++ -c main.cpp

menu.o: menu.cpp menu.h
	g++ -c menu.cpp

account.o: account.cpp account.h
	g++ -c account.cpp

account_settings.o: account_settings.cpp account_settings.h
	g++ -c account_settings.cpp

bank_account.o: bank_account.cpp bank_account.h
	g++ -c bank_account.cpp

stock_account.o: stock_account.cpp stock_account.h
	g++ -c stock_account.cpp

clean:
	rm *.o account_system