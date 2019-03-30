#include "honeyClass.h"
#include "Database.h"
#include "Random.h"

QString currentClassName="";
QList<StudentInfo> currentStudentList;

honeyClass::honeyClass(QWidget *parent):QWidget(parent)
{
	ui.setupUi(this);
	Init();
	this->setWindowIcon(QIcon("./Icon/form.ico"));
	this->setWindowState(Qt::WindowMaximized);
	lineSignalAndSlot();
	
}

void honeyClass::InitCurrentClassName(const QString &text)
{
	currentClassName =text;
	if (currentClassName == "请选择班级")
	{
		currentClassName ="";
	}

	QList<StudentInfo> StudentList = DataBase::getStudentInfo();
	QFile *file = new QFile((QString("./") + currentClassName + ".txt"));
	if (file->exists())
	{
		file->open(QIODevice::ReadOnly);
		QList<int> indexList;
		QTextStream textIn(file);
		for (int i = 0; i < StudentList.count(); i++)
		{
			int m;
			textIn >> m;
			indexList.append(m);
		}
		file->close();
		delete file;
		currentStudentList.clear();
		for (int i = 0; i < StudentList.count(); i++)
		{
			currentStudentList.append(StudentList[indexList[i]]);
		}
		return;
	}
	else
	{
		currentStudentList = StudentList;
	}	
}

void honeyClass::lineSignalAndSlot()
{
	connect(functionTree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(GetFunction(QTreeWidgetItem*, int)));
	connect(this, SIGNAL(clickedShuffer()), this, SLOT(Shuffer()));
	connect(this, SIGNAL(clickedChooseOneByRandom()), this, SLOT(ChooseOneByRandom()));
	connect(this, SIGNAL(clickedChooseOneBoy()), this, SLOT(ChooseOneBoy()));
	connect(this, SIGNAL(clickedChooseOneGirl()), this, SLOT(ChooseOneGirl()));
	connect(this, SIGNAL(clickedChooseTwoByRandom()), this, SLOT(ChooseTwoByRandom()));
	connect(this, SIGNAL(clickedChooseBoyAndGirl()), this, SLOT(ChooseBoyAndGirl()));
	connect(this, SIGNAL(clickedChooseTwoBoy()), this, SLOT(ChooseTwoBoy()));
	connect(this, SIGNAL(clickedChooseTwoGirl()), this, SLOT(ChooseTwoGirl()));
	connect(this, SIGNAL(clickedArrangeOneByOne()), this, SLOT(ArrangeOneByOne()));
	connect(this, SIGNAL(clickedArrangeTwo()), this, SLOT(ArrangeTwo()));
	connect(this, SIGNAL(clickedShowStudentInformation()), this, SLOT(ShowStudentInformation()));
	connect(this, SIGNAL(clickedDeleteStudentInformation()), this, SLOT(DeleteStudentInformation()));
	connect(this, SIGNAL(clickedImportStudentInformation()), this, SLOT(ImportStudentInformation()));
	connect(this, SIGNAL(clickedView()), this, SLOT(View()));
	connect(this, SIGNAL(clickedCreateFirstForm()), this, SLOT(CreateFirstForm()));
	connect(this, SIGNAL(clickedCreateThirdForm()), this, SLOT(CreateThirdForm()));
	connect(classChooseButton, SIGNAL(currentTextChanged(const QString)), this, SLOT(InitCurrentClassName(const QString)));
	connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
	
}

bool honeyClass::eventFilter(QObject *obj, QEvent *ev)
{
	if (obj == this)
	{
		if (ev->type() == QEvent::Close)
		{
			closeAllTab();
			return true;
		}
		return false;
	}
	return honeyClass::eventFilter(obj, ev);
}

void honeyClass::closeAllTab()
{
	QString str="";
	allClose = true;
	while(tabWidget->count()>0)
	{
		str = tabWidget->tabText(0);
		if (str.mid(str.count() - 4) == "座位视图")
		{
			classChooseButton->setCurrentText(str.mid(0, str.count() - 4));
			closeTab(0);
			continue;
		}
		tabWidget->removeTab(0);
	}
}

void honeyClass::closeTab(int index)
{
	qDebug() << tabWidget->count();
	QString str = tabWidget->tabText(index);
	if (str.mid(str.count() - 4) != "座位视图")
	{
		tabWidget->removeTab(index);
		return;
	}
	int result=QMessageBox::No;
	if (!allClose)
	{
		result = QMessageBox::information(this, "消息", QString("是否保留") + tabWidget->tabText(index) + "，以便以后使用", QMessageBox::Yes | QMessageBox::Cancel | QMessageBox::No);
	}
	else
	{
		result = QMessageBox::information(this, "消息", QString("是否保留") + tabWidget->tabText(index) + "，以便以后使用", QMessageBox::Yes | QMessageBox::No);
	}
	if (result == QMessageBox::Yes)
	{
		QFile *file=new QFile((QString("./")+currentClassName + ".txt"));
		if (!file->exists())
		{
			file->open(QIODevice::WriteOnly);
			file->close();
			file = new QFile((QString("./") + currentClassName + ".txt"));
		}
		file->open(QIODevice::WriteOnly);
		QTextStream textout(file);
		for (int i = 0; i < currentStudentList.count(); i++)
		{
			textout << currentStudentList[i].getIndex() << " ";
		}
		file->close();
		delete file;
	}
	else if(result==QMessageBox::No)
	{
	}
	else if (result == QMessageBox::Cancel)
	{
		return;
	}
	tabWidget->removeTab(index);
}

QWidget* honeyClass::CreateFirstForm()
{
	for (int i = 0; i < tabWidget->count(); i++)
	{
		if ((currentClassName + "座位视图") == tabWidget->tabText(i))
		{
			tabWidget->setTabEnabled(i, true);
			tabWidget->setCurrentIndex(i);
			((FirstForm*)(tabWidget->currentWidget()))->recoverColor();
			return tabWidget->currentWidget();
		}
	}
	FirstForm* newTab = new FirstForm();
	tabWidget->addTab(newTab, currentClassName + "座位视图");
	tabWidget->setCurrentWidget(newTab);
	return tabWidget->currentWidget();
}


void honeyClass::Shuffer()
{
	FirstForm* form=(FirstForm*)CreateFirstForm();
	currentStudentList = Random::sufferList(currentStudentList);
	form->setSeatsText(currentStudentList);
}

void honeyClass::ChooseOneByRandom()
{
	FirstForm* form = (FirstForm*)CreateFirstForm();
	form->setDifferentColor(Random::random(currentStudentList.count()));
}

void honeyClass::ChooseOneBoy()
{
	FirstForm* form = (FirstForm*)CreateFirstForm();
	QList<StudentInfo> boyList = getBoyList();
	if (boyList.count() == 0)
	{
		QMessageBox::information(this, "警告", "没有搜索到女生，也许系统除了问题，请检查您的班级信息");
		return;
	}
	int i;
	for (i = 0; i < currentStudentList.count(); i++)
	{
		if (currentStudentList[i].getIndex() == boyList[Random::random(boyList.count())].getIndex())
		{
			break;
		}
	}
	form->setDifferentColor(i);
}

void honeyClass::ChooseOneGirl()
{
	FirstForm* form = (FirstForm*)CreateFirstForm();
	QList<StudentInfo> girlList = getGirlList();
	if (girlList.count() == 0)
	{
		QMessageBox::information(this, "警告", "没有搜索到女生，也许系统出了问题，请检查您的班级信息");
		return;
	}
	int i;
	for ( i = 0; i < currentStudentList.count(); i++)
	{
		if (currentStudentList[i].getIndex() == girlList[Random::random(girlList.count())].getIndex())
		{
			break;
		}
	}
	form->setDifferentColor(i);
}

void honeyClass::ChooseTwoByRandom()
{
	FirstForm* form = (FirstForm*)CreateFirstForm();
	int num = currentStudentList.count();
	if (num < 2)
	{
			QMessageBox::information(this, "警告", "您的班级不足两人，也许系统出了问题，请检查您的班级信息");
			return;
	}
	int a=Random::random(num);
	int b = Random::random(num);
	while (b == a)
	{
		b = Random::random(num);
	}
	qDebug() << num << endl;
	qDebug() << "a=" << a << ";b=" << b << endl;
	form->setDifferentColor(a);
	form->setDifferentColor(b);
}

void honeyClass::ChooseBoyAndGirl()
{
	FirstForm* form = (FirstForm*)CreateFirstForm();
	QList<StudentInfo> boyList = getBoyList();
	QList<StudentInfo> girlList = getGirlList();
	int boynum = boyList.count();
	int girlnum = girlList.count();
	int randomGirlNum = Random::random(girlnum);
	int randomBoyNum = Random::random(boynum);
	if (boynum < 1)
	{
		QMessageBox::information(this, "警告", "您的班级男生人数不足，也许系统出了问题，请检查您的班级信息");
		return;
	}
	if (girlnum < 1)
	{
		QMessageBox::information(this, "警告", "您的班级女生人数不足，也许系统出了问题，请检查您的班级信息");
		return;
	}

	int i;
	for (i = 0; i < currentStudentList.count(); i++)
	{
		if (currentStudentList[i].getIndex() == girlList[randomGirlNum].getIndex())
		{
			break;
		}
	}
	int j;
	for (j = 0; j < currentStudentList.count(); j++)
	{
		if (currentStudentList[j].getIndex() == boyList[randomBoyNum].getIndex())
		{
			break;
		}
	}

	form->setDifferentColor(i);
	form->setDifferentColor(j);
}

void honeyClass::ChooseTwoBoy()
{
	FirstForm* form = (FirstForm*)CreateFirstForm();
	QList<StudentInfo> boyList = getBoyList();
	int num = boyList.count();
	if (num < 2)
	{
		QMessageBox::information(this, "警告", "您的班级男生不足两人，也许系统出了问题，请检查您的班级信息");
		return;
	}

	int a = Random::random(num);
	int indexBoy1 =boyList[a].getIndex();
	boyList.removeAt(a);
	int b = Random::random(boyList.count());
	int indexBoy2 = boyList[b].getIndex();

	int i;
	for (i = 0; i < currentStudentList.count(); i++)
	{
		if (currentStudentList[i].getIndex() == indexBoy1)
		{
			break;
		}
	}
	int j;
	for (j = 0; j < currentStudentList.count(); j++)
	{
		if (currentStudentList[j].getIndex() == indexBoy2)
		{
			break;
		}
	}
	form->setDifferentColor(i);
	form->setDifferentColor(j);
}

void honeyClass::ChooseTwoGirl()
{
	FirstForm* form = (FirstForm*)CreateFirstForm();
	QList<StudentInfo> girlList = getGirlList();
	int num = girlList.count();
	if (num < 2)
	{
		QMessageBox::information(this, "警告", "您的班级女生不足两人，也许系统出了问题，请检查您的班级信息");
		return;
	}

	int a = Random::random(num);
	int indexGirl1= girlList[a].getIndex();
	girlList.removeAt(a);
	int b = Random::random(girlList.count());
	int indexGirl2= girlList[b].getIndex();
	int i;
	for (i = 0; i < currentStudentList.count(); i++)
	{
		if (currentStudentList[i].getIndex() == indexGirl1)
		{
			break;
		}
	}
	int j;
	for (j = 0; j < currentStudentList.count(); j++)
	{
		if (currentStudentList[j].getIndex() == indexGirl2)
		{
			break;
		}
	}
	form->setDifferentColor(i);
	form->setDifferentColor(j);
}

void honeyClass::ArrangeOneByOne()
{
	SecondForm *newSecondForm = new SecondForm(this, 1);
	tabWidget->addTab(newSecondForm, currentClassName + "单人随机列表");
	tabWidget->setCurrentWidget(newSecondForm);
}

void honeyClass::ArrangeTwo()
{
	SecondForm *newSecondForm = new SecondForm(this, 2);
	tabWidget->addTab(newSecondForm, currentClassName + "双人随机列表");
	tabWidget->setCurrentWidget(newSecondForm);
}

void honeyClass::ShowStudentInformation()
{
	ThirdForm *thirdForm = new ThirdForm();
	thirdForm->setVisible(true);
	tabWidget->addTab(thirdForm, QString("显示") + currentClassName + "信息");
	tabWidget->setCurrentWidget(thirdForm);
}

void honeyClass::DeleteStudentInformation()
{
	int result = QMessageBox::information(this, "警告", QString("您确定删除")+currentClassName+"班级相关的所有信息吗？", QMessageBox::Yes | QMessageBox::No);
	if (result == QMessageBox::Yes)
	{
		QSqlDatabase *database = DataBase::readDatabase();
		QSqlQuery query;
		query.exec("Drop table " + currentClassName);
		database->close();
		QMessageBox::information(this, "提示", "请手动重启软件");
	}		
}

void honeyClass::ImportStudentInformation()
{
	QMessageBox::information(this, "步骤引导第一步", "请选择用excel编辑,从第一行开始，共四列，分别为学号，姓名，性别，学院");
	QMessageBox::information(this, "步骤引导第二步", "文件另存为\"CSV UTF-8(逗号分隔)(*.csv文件)");
	QMessageBox::information(this, "步骤引导第三步", "导出文件右键，重命名为班级名.csv，例如111班的文件名为class111.csv");
	QMessageBox::information(this, "步骤引导第四步", "单击确定后，在弹出的窗口中选择导出文件路径");
	QFileDialog* fd = new QFileDialog(this);//创建打开文件对话框  
	QString fileName = fd->getOpenFileName(this, tr("Open File"), "/home", tr("Excel(*.csv)"));
	if (fileName == "")
	{
		QMessageBox::information(this, "提示", "fail to open the file");
		return;
	}	
	QDir dir = QDir::current();
	QFile file(dir.filePath(fileName));
	QString importFileName = QFileInfo(fileName).fileName();
	QString tableName = importFileName.mid(0,importFileName.count() - 4);

	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(this, "提示","fail to open the file");
	}		
	QTextStream * out = new QTextStream(&file);//文本流  
	QStringList tempOption = out->readAll().split("\n");//每行以\n区分  

	QSqlDatabase *database = DataBase::readDatabase();
	QSqlQuery query;
	query.exec("CREATE TABLE "+tableName+"(Id Text,Name Text,Sex Text,Place Text)");
	for (int i = 0; i < tempOption.count()-1; i++)
	{
		QStringList tempbar = tempOption.at(i).split(",");//一行中的单元格以，区分   
		QString Id;
		QString Name;
		QString Sex;
		QString Place;
		Id = tempbar[0].replace("\"", "");
		Name= tempbar[1].replace("\"", "");
		Sex= tempbar[2].replace("\"", "");
		Place = tempbar[3].replace("\"", "");
		query.exec("INSERT INTO "+tableName+" VALUES('"+Id+"','"+Name+"','"+Sex+"','"+Place+"')");
	}
	database->close();
	QMessageBox::information(this, "提示", "导入数据完成,请手动重启程序");
	file.close();//操作完成后记得关闭文件 
}

void honeyClass::View()
{
	CreateFirstForm();
}


void honeyClass::Init()
{	
	allClose = false;
	this->installEventFilter(this);
	splitter = new QSplitter(this);
	classChooseButton = new QComboBox(this);
	CreateFunctionTree();
	CreateCombobox();
	QGroupBox *leftBox = new QGroupBox();
	QVBoxLayout *vbox = new QVBoxLayout();

	QScrollArea *scrollAreaLeft=new QScrollArea(this);
	scrollAreaLeft->setWidget(functionTree);
	scrollAreaLeft->setVisible(true);
	scrollAreaLeft->setWidgetResizable(true);
	scrollAreaLeft->setBackgroundRole(QPalette::Base);

	vbox->addWidget(scrollAreaLeft);
	vbox->addWidget(classChooseButton);
	leftBox->setLayout(vbox);
	splitter->addWidget(leftBox);
	QGroupBox *rightBox = new QGroupBox();
	QHBoxLayout *box = new QHBoxLayout();

	tabWidget = new QTabWidget();
	tabWidget->setTabsClosable(true);
	tabWidget->setMovable(true);
	QScrollArea *scrollAreaRight=new QScrollArea(this);
	scrollAreaRight->setWidget(tabWidget);
	scrollAreaRight->setVisible(true);

	scrollAreaRight->setWidgetResizable(true);
	scrollAreaRight->setBackgroundRole(QPalette::Base);
	box->addWidget(scrollAreaRight);

	rightBox->setLayout(box);
	splitter->addWidget(rightBox);
	splitter->setHandleWidth(0);
	splitter->setStretchFactor(0, 1);
	splitter->setStretchFactor(1, 20);
	splitter->setAutoFillBackground(true);
	QGridLayout *gridLayout = new QGridLayout();
	gridLayout->addWidget(splitter);
	this->setLayout(gridLayout);
}

void honeyClass::CreateFunctionTree()
{
	functionTree = new QTreeWidget(splitter);
	functionTree->setColumnCount(1);
	functionTree->setHeaderLabel("控制台");

	//创建第一层结点
	QTreeWidgetItem *showSingleSiteRootIterm = new QTreeWidgetItem(functionTree,QStringList()<<"位置视图功能");
	showSingleSiteRootIterm->setIcon(0, QIcon("./Icon/add.ico"));

	QTreeWidgetItem *showComplexRootIterm = new QTreeWidgetItem(functionTree, QStringList() << "列表视图功能");
	showComplexRootIterm->setIcon(0, QIcon("./Icon/add.ico"));

	QTreeWidgetItem *setRootItem = new QTreeWidgetItem(functionTree, QStringList() << "设置");
	setRootItem->setIcon(0, QIcon("./Icon/add.ico"));


	QTreeWidgetItem *SingleIterm_shuffer = new QTreeWidgetItem(showSingleSiteRootIterm, QStringList() << "随机打乱座位");
	SingleIterm_shuffer->setIcon(0, QIcon("./Icon/home.ico"));
	QTreeWidgetItem *SingleIterm_choose1 = new QTreeWidgetItem(showSingleSiteRootIterm, QStringList() << "随机挑选一位");
	SingleIterm_choose1->setIcon(0, QIcon("./Icon/add.ico"));
	QTreeWidgetItem *SingleIterm_choose2 = new QTreeWidgetItem(showSingleSiteRootIterm, QStringList() << "随机挑选两位");
	SingleIterm_choose2->setIcon(0, QIcon("./Icon/add.ico"));
	
	QTreeWidgetItem *SingleIterm_choose1_random = new QTreeWidgetItem(SingleIterm_choose1, QStringList() << "不区分性别");
	SingleIterm_choose1_random->setIcon(0, QIcon("./Icon/home.ico"));
	QTreeWidgetItem *SingleIterm_choose1_b = new QTreeWidgetItem(SingleIterm_choose1, QStringList() << "挑选一位男生");
	SingleIterm_choose1_b->setIcon(0, QIcon("./Icon/home.ico"));
	QTreeWidgetItem *SingleIterm_choose1_girl = new QTreeWidgetItem(SingleIterm_choose1, QStringList() << "挑选一位女生");
	SingleIterm_choose1_girl->setIcon(0, QIcon("./Icon/home.ico"));

	QTreeWidgetItem *SingleIterm_choose2_bg = new QTreeWidgetItem(SingleIterm_choose2, QStringList() << "不区分性别");
	SingleIterm_choose2_bg->setIcon(0, QIcon("./Icon/home.ico"));
	QTreeWidgetItem *SingleIterm_choose2_random = new QTreeWidgetItem(SingleIterm_choose2, QStringList() << "男+女");
	SingleIterm_choose2_random->setIcon(0, QIcon("./Icon/home.ico"));
	QTreeWidgetItem *SingleIterm_choose2_bb = new QTreeWidgetItem(SingleIterm_choose2, QStringList() << "两男");
	SingleIterm_choose2_bb->setIcon(0, QIcon("./Icon/home.ico"));
	QTreeWidgetItem *SingleIterm_choose2_gg= new QTreeWidgetItem(SingleIterm_choose2, QStringList() << "两女");
	SingleIterm_choose2_gg->setIcon(0, QIcon("./Icon/home.ico"));

	QTreeWidgetItem *ComplexIterm_single = new QTreeWidgetItem(showComplexRootIterm, QStringList() << "全班单人顺序排列");
	ComplexIterm_single->setIcon(0, QIcon("./Icon/home.ico"));
	QTreeWidgetItem *ComplexIterm_pair = new QTreeWidgetItem(showComplexRootIterm, QStringList() << "全班双人顺序排列");
	ComplexIterm_pair->setIcon(0, QIcon("./Icon/home.ico"));

	QTreeWidgetItem *setRootItem_edit = new QTreeWidgetItem(setRootItem, QStringList() << "显示学生信息");
	setRootItem_edit->setIcon(0, QIcon("./Icon/home.ico"));
	QTreeWidgetItem *setRootItem_new = new QTreeWidgetItem(setRootItem, QStringList() << "不再使用当前班级信息");
	setRootItem_new->setIcon(0, QIcon("./Icon/home.ico"));
	QTreeWidgetItem *setRootItem_import = new QTreeWidgetItem(setRootItem, QStringList() << "导入学生信息");
	setRootItem_import->setIcon(0, QIcon("./Icon/home.ico"));

	QTreeWidgetItem *showSiteRootIterm = new QTreeWidgetItem(functionTree, QStringList() << "座位视图");
	showSiteRootIterm->setIcon(0, QIcon("./Icon/view.ico"));

	functionTree->expandAll();
}


void honeyClass::CreateCombobox()
{
	classChooseButton->setEditable(false);
	classChooseButton->view()->setAlternatingRowColors(true);
	classChooseButton->setStyleSheet("QComboBox { min-height: 20px;font: 75 10pt \"Consolas\";}");
	classChooseButton->addItem(QIcon("./Icon/view.ico"), "请选择班级");
	QSqlDatabase *database = DataBase::readDatabase();
	QStringList databaseTablesNames = database->tables();
	for (int i = 0; i <databaseTablesNames.count(); i++)
	{
		classChooseButton->addItem(QIcon("./Icon/view.ico"),databaseTablesNames[i]);
	}	
	database->close();
}

void honeyClass::GetFunction(QTreeWidgetItem *item,int column)
{
	if (currentClassName == ""&&item->text(0)!="导入学生信息")
	{
		QMessageBox::information(this, "警告", "请在左下角选择班级", QMessageBox::YesRole);
		return;
	}
	if (item->text(0) == "随机打乱座位")
	{
		emit clickedShuffer();
	}
	else if (item->text(0) == "不区分性别"&&item->parent()->text(0)=="随机挑选一位")
	{
		emit clickedChooseOneByRandom();
	}
	else if (item->text(0) == "挑选一位男生")
	{
		emit clickedChooseOneBoy();
	}
	else if (item->text(0) == "挑选一位女生")
	{
		emit clickedChooseOneGirl();
	}
	else if (item->text(0) == "不区分性别"&&item->parent()->text(0) == "随机挑选两位")
	{
		emit clickedChooseTwoByRandom();
	}
	else if (item->text(0) == "男+女")
	{
		emit clickedChooseBoyAndGirl();
	}
	else if (item->text(0) == "两男")
	{
		emit clickedChooseTwoBoy();
	}
	else if (item->text(0) == "两女")
	{
		emit clickedChooseTwoGirl();
	}
	else if (item->text(0) == "全班单人顺序排列")
	{
		emit clickedArrangeOneByOne();
	}
	else if (item->text(0) == "全班双人顺序排列")
	{
		emit clickedArrangeTwo();
	}
	else if (item->text(0) == "显示学生信息")
	{
		emit clickedShowStudentInformation();		
	}
	else if (item->text(0) == "不再使用当前班级信息")
	{
		emit  clickedDeleteStudentInformation();
	}
	else if (item->text(0) == "导入学生信息")
	{
		emit  clickedImportStudentInformation();
	}
	else if (item->text(0) == "座位视图")
	{
		emit clickedView();
	}
	else if (item->text(0) == "位置视图功能"|| item->text(0) == "座位视图"|| item->text(0) == "随机挑选两位"|| item->text(0) == "随机挑选一位")
	{
		emit clickedCreateFirstForm();
	}
	else if (item->text(0) == "设置")
	{
		emit clickedCreateThirdForm();
	}
}

honeyClass::~honeyClass()
{
	delete classChooseButton;
	delete functionTree;
	delete tabWidget;
	delete splitter;
}

QList<StudentInfo> honeyClass::getBoyList()
{
	QList<StudentInfo> boylist;
	for (int i = 0; i < currentStudentList.count(); i++)
	{
		StudentInfo student = currentStudentList[i];
		if (student.getSex() == "男")
		{
			boylist.append(student);
		}
	}
	return boylist;
}

QList<StudentInfo> honeyClass::getGirlList()
{
	QList<StudentInfo> girllist;
	for (int i = 0; i < currentStudentList.count(); i++)
	{
		StudentInfo student = currentStudentList[i];
		if (student.getSex() == "女")
		{
			girllist.append(student);
		}
	}
	return girllist;
}