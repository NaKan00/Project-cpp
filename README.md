Имеется три исполнительных файла k_means.exe, k_medoids.exe, hca.exe.
Каждый из исполняемых файлов имеет одинаковый интерфейс, поэтому следующее описание относится ко всем.

Перед запуском программы необходимо открыть терминал. Для этого необходимо:
	1)нажать сочетание клавиш WIN+R 
	2)в открывшемся окне вписать "cmd"
	3)нажать кнопку "OK"
Далее для удобства рекомендуется перейти в папку с проектом следующей командой:
	cd <PROJECT_PATH>
где 
	<PROJECT_PATH> - путь до дирректории с проектом 

При запуске метода кластеризации необходимо указать 4 обязательных ключа :-ifile,-ofile,-ncl,-stat в любом порядке

Для запуска кластеризации необходимо выполнить следующую консольную команду :
	<EXE_FILE_NAME> -ifile <INPUT_FILE_NAME> -ofile <OUTPUT_FILE_NAME> -ncl <NUM_OF_CLUSTERS> -stat <STATISTICS_FILE_NAME>
где 
	<EXE_FILE_NAME> - путь+имя исполняемого файла пример "C:/Users/USER/Documents/cppCode/k_means.exe", если исполняемый файл находится в данной дирректории путь указывается как "./" пример "./k_means.exe", вырианты исполняемых файлов : "k_means.exe", "k_medoids.exe", "hca.exe";
	<INPUT_FILE_NAME> - путь+имя файла с кластеризируемыми данными  пример "C:/Users/USER/Documents/cppCode/marketing_campaign.csv.xls", если данный файл находится в данной дирректории путь указывается как "./" пример "./marketing_campaign.csv.xls";
	<OUTPUT_FILE_NAME> - путь+имя файла куда необходимо записать результат  пример "C:/Users/USER/Documents/cppCode/clusters.txt", если данный файл находится в данной дирректории путь указывается как "./" пример "./clusters.txt"
	<NUM_OF_CLUSTERS> - Целое число, колличество кластеров на которые необходио разбить датасет , пример "4"
	<STATISTICS_FILE_NAME> - путь+имя файла куда необходимо записать силуэтные коэффициенты пример "C:/Users/USER/Documents/cppCode/stat.csv.xls", если данный файл находится в данной дирректории путь указывается как "./" пример "./stat.csv.xls"
Пример итоговой команды вызова :
	.\k_means.exe -ifile marketing_campaign.csv.xls -ofile clusters.txt -ncl 4 -stat stat.csv.xls
ПРИМЕЧАНИЕ: если в пути содержатся папки на кириллеци или содержащие пробелы, весь путь+имя обрамить в двойные кавычки.
