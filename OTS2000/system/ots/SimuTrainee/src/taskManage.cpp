#include "taskManage.h"
#include "Login.h"

CTaskManage *taskManage;

// CTaskManageWidget::CTaskManageWidget()
// {
// 	setupUi(this);
// 	dlg_created_flag[TASKDLG] = true;
// 	this->setAttribute(Qt::WA_DeleteOnClose);
// }
// CTaskManageWidget::~CTaskManageWidget()
// {
// 	dlg_created_flag[TASKDLG] = false;
// }

CTaskManage::CTaskManage(QWidget* parent)
:QWidget(parent)
{
	if (m_taskmanage_count<1)
	{
		flagthread = true;
	}
	else
		flagthread = false;
	m_taskmanage_count++;
	if (m_taskmanage_count>1)
	{
			dlg_created_flag[TASKDLG] = true;
	}
	this->setAttribute(Qt::WA_DeleteOnClose);
	setupUi(this);
	if (flag_langueage == 0)
	{
		loadChinese();
	}
	else if (flag_langueage == 1)
	{
		loadEnglish();
	}	
	init();
	this->setObjectName("task_manage");
	connect(buttonExit,SIGNAL(clicked()),this,SLOT(onexit()));
	connect(buttonStart,SIGNAL(clicked()),this,SLOT(taskStart()));
	connect(buttonReStart,SIGNAL(clicked()),this,SLOT(taskReStart()));
	connect(buttonFinish,SIGNAL(clicked(bool)),this,SLOT(taskFinish(bool)));
	connect(buttonSetCurTask,SIGNAL(clicked()),this,SLOT(setCurTask()));
	connect(buttonDelTask,SIGNAL(clicked()),this,SLOT(delTask()));
	connect(buttonClearTask,SIGNAL(clicked()),this,SLOT(clearTaskList()));
	connect(timerTaskTime,SIGNAL(timeout()),this,SLOT(taskTimeCountDown()));
	connect(this,SIGNAL(sigTimeOut()),this,SLOT(timeOut()));
	connect(checkSimuTip,SIGNAL(stateChanged(int)),this,SLOT(switchSimuTip(int)));
	connect(listTaskRec,SIGNAL(entered(const QModelIndex &)),this,SLOT(PopupTaskRecDetail(const QModelIndex &)));
	connect(tabWidget,SIGNAL(currentChanged(int )),this,SLOT(displayTaskRec(int)));
}
CTaskManage::~CTaskManage()
{
	m_taskmanage_count--;
	if (m_taskmanage_count <=1)
	{
		dlg_created_flag[TASKDLG] = false;
	}
}
void CTaskManage::showEvent(QShowEvent *event)
{
// 	displayTaskRec();//dzy
// 	if (shm_ots_addr->simu_mode>0&&taskList->isVisible()||shm_ots_addr->simu_mode>0&&taskRec->isVisible())
// 	{
// 		taskList->setVisible(false);
// 		taskRec->setVisible(false);
// 		taskList->setEnabled(false);
// 		taskRec->setEnabled(false);
// 		tabWidget->setCurrentIndex(0);
// 	}
// 	else if (!taskList->isVisible()||!taskRec->isVisible())
// 	{
// 		taskList->setVisible(true);
// 		taskRec->setVisible(true);
// 		taskList->setEnabled(true);
// 		taskRec->setEnabled(true);
// 		tabWidget->setCurrentIndex(0);
// 	}
// 	if (flag_langueage == 0)
// 	{
// 		loadChinese();
// 	}
// 	else if (flag_langueage == 1)
// 	{
// 		loadEnglish();
// 	}
	event->accept();
}
void CTaskManage::loadChinese()
{
	QTranslator translator;
	translator.load("SimuTrainee_zh_CN");
	qApp->installTranslator(&translator);
	retranslateUi(this);
}
void CTaskManage::loadEnglish()
{
	QTranslator translator;
	translator.load("SimuTrainee_en");
	qApp->installTranslator(&translator);
	retranslateUi(this);
}
void  CTaskManage::setLanguage(int language)
{	
	QTranslator translator;
	if (language == 0)
	{
		translator.load("SimuTrainee_zh_CN");
	}
	else if (language == 1)
	{
		translator.load("SimuTrainee_en");
	}
	qApp->installTranslator(&translator);
	retranslateUi(this);
}
void CTaskManage::init()
{
	task_num = 0;
	timerTaskTime = new QTimer;
	selectionModel = listTask->selectionModel();
	listTask->setSelectionBehavior(QAbstractItemView::SelectRows);
	listTask->setEditTriggers(QTableWidget::NoEditTriggers);
	listTask->setSelectionMode(QAbstractItemView::SingleSelection);
	listTaskRec->setSelectionBehavior(QAbstractItemView::SelectRows);
	listTaskRec->setEditTriggers(QTableWidget::NoEditTriggers);
	listTaskRec->setSelectionMode(QAbstractItemView::SingleSelection);
	listTaskRec->verticalHeader()->setVisible(false);
	listTask->setColumnWidth(0,330);
	listTask->setColumnWidth(1,130);
	listTask->setColumnWidth(2,60);
	listTask->horizontalHeader()->setStretchLastSection(true);
	listTaskRec->setColumnWidth(0,550);
	listTaskRec->horizontalHeader()->setStretchLastSection(true);
	//listTask->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	taskTime->setFixedSize(QSize(130,27));
	taskTime->setNumDigits(8);
	taskTime->setSegmentStyle(QLCDNumber::Filled);
	//taskTime->setStyleSheet("");
	listTask->clearContents();
	tabWidget->setCurrentIndex(0);
	clearCurTask();
}
void CTaskManage::clearCurTask()
{
	cur_task_info.send_task_id = -1;
	cur_task_info.task_id = -1;
	cur_task_info.task_name = QString::fromLocal8Bit("当前无任务");
	cur_task_info.scene_id = -1;
	cur_task_info.scene_name.clear();
	cur_task_info.fault_id = -1;
	cur_task_info.fault_name.clear();
	cur_task_info.stn_id = -1;
	cur_task_info.stn_name.clear();
	cur_task_info.dev_id = -1;
	cur_task_info.dev_name.clear();
	cur_task_info.task_tip.clear();
	cur_task_info.type = 0;
	cur_task_info.time_len = 0;
	cur_task_info.task_time = QTime(0,0,0);
	cur_task_info.score = 0;
	cur_task_info.is_record = 0;
	cur_task_info.send_time.clear();
	cur_task_info.start_time.clear();
	cur_task_info.end_time.clear();
	cur_task_info.status = -1;
	cur_task_info.task_status = -1;
	taskTime->display("00:00:00");
	labelTaskName->setText(QString::fromLocal8Bit("当前无任务"));
	labelTaskAttr->clear();
	labelSendTime->clear();
	labelStation->clear();
	labelDev->clear();
	labelStatus->clear();
	labelScene->clear();
	labelFault->clear();
	textTaskTip->clear();
	buttonStart->setEnabled(false);
	buttonReStart->setEnabled(false);
	buttonFinish->setEnabled(false);
	emit sigTaskTimeChanged(cur_task_info.task_time);
}
void CTaskManage::taskStart()
{
	if (cur_task_info.task_status != 1||shm_ots_addr->data_task.task_startable == 0)
		return;
	DB_FMT data;
	data.table_id = TABLE_TRAIN_INFO;
	InitDbData(&data,data.table_id);
	data.cond_flag.flag_train_info.host_id=TRUE;
	data.cond_seg.seg_train_info.host_id=g_host_id;

	data.flag.flag_train_info.send_task_id=TRUE;
	data.seg.seg_train_info.send_task_id=cur_task_info.send_task_id;
	data.flag.flag_train_info.task_id=TRUE;
	data.seg.seg_train_info.task_id=cur_task_info.task_id;
	data.flag.flag_train_info.scene_id=TRUE;
	data.seg.seg_train_info.scene_id=cur_task_info.scene_id;
	data.flag.flag_train_info.fault_id=TRUE;
	data.seg.seg_train_info.fault_id=cur_task_info.fault_id;
	data.flag.flag_train_info.status=TRUE;
	data.seg.seg_train_info.status=1;
	if (UpdateOneRec(&data)!=TRUE)
	{
		HdbLogWrite(data.sql_str,data.sql_error);
		FreeDbData(&data,TABLE_TRAIN_INFO);
		return;
	}
	FreeDbData(&data,TABLE_TRAIN_INFO);
	data.table_id = TABLE_SEND_TASK;
	InitDbData(&data,data.table_id);
	data.cond_flag.flag_send_task.send_task_id = TRUE;
	data.cond_seg.seg_send_task.send_task_id = cur_task_info.send_task_id;

	data.flag.flag_send_task.start_time = TRUE;
	GetCurTimeStr(data.seg.seg_send_task.start_time);
	cur_task_info.start_time = QString::fromLocal8Bit(data.seg.seg_send_task.start_time);
	data.flag.flag_send_task.status = TRUE;
	data.seg.seg_send_task.status = 2;
	if (UpdateOneRec(&data)!=TRUE)
	{
		HdbLogWrite(data.sql_str,data.sql_error);
		FreeDbData(&data,TABLE_SEND_TASK);
		return;
	}
	FreeDbData(&data,TABLE_SEND_TASK);
	buttonStart->setEnabled(false);
	buttonReStart->setEnabled(true);
	buttonFinish->setEnabled(true);
	cur_task_info.task_status = 2;
	shm_ots_addr->data_task.task_status = 2;
	labelStatus->setText(QString::fromLocal8Bit("任务已启动"));
	if (shm_ots_addr->simu_mode==0)
		listTask->setItem(listTask->findItems(cur_task_info.task_name,Qt::MatchContains).at(0)->row(),3,new QTableWidgetItem(QString::fromLocal8Bit("任务已启动")));
	emit sigTaskStarted();
	if (!timerTaskTime->isActive())
		timerTaskTime->start(1000);
	if (CheckUserPrivilege(login_user_id,StudentPrivType::PRIV_SIMU_TIP,shm_ots_addr->simu_mode))
	{
		//DZY 140618
		DB_FMT data2;
		data2.table_id = TABLE_SUBJECT;
		InitDbData(&data2,data2.table_id);
		data2.cond_flag.flag_subject.task_id=TRUE;
		data2.cond_seg.seg_subject.task_id=cur_task_info.task_id;
		SelectRecs(&data2);
		if (data2.rownum>=1 &&shm_ots_addr->simu_mode==0)
		{
			if (dlgSimuTip==NULL)
			{
				dlgSimuTip = new CSimuTipDlg(NULL,cur_task_info.task_id,cur_task_info.send_task_id);
				if (checkSimuTip->checkState() == Qt::Checked)
					dlgSimuTip->show();
				return;
			}	
			else if (dlgSimuTip->isHidden())
			{
				dlgSimuTip->~CSimuTipDlg();
				dlgSimuTip = new CSimuTipDlg(NULL,cur_task_info.task_id,cur_task_info.send_task_id);
				if (checkSimuTip->checkState() == Qt::Checked)
					dlgSimuTip->show();
				return;				
			}
		}	
	}
}
void CTaskManage::taskReStart()
{
	QMessageBox msgBox(this);
	msgBox.setIcon(QMessageBox::Information);
	msgBox.setWindowTitle (QString::fromLocal8Bit("提示"));
	msgBox.setInformativeText(QString::fromLocal8Bit("任务重新启动，将删除之前该任务操作记录，是否重启该任务？"));
	msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Ok);
	if (msgBox.exec() == QMessageBox::Cancel) 
	{
		return;
	}
	else
	{	
		if (dlgSimuTip != NULL)	//dzy
		{
			dlgSimuTip->close();
			dlgSimuTip->~CSimuTipDlg();
			dlgSimuTip = NULL;
		}	
		DB_FMT data;
		data.table_id = TABLE_RECORD;
		InitDbData(&data,data.table_id);
		data.cond_flag.flag_record.send_task_id=TRUE;
		data.cond_seg.seg_record.send_task_id=cur_task_info.send_task_id;
		DeleteOneRec(&data);
	}
	cur_task_info.task_status = 1;
	cur_task_info.task_time = QTime(cur_task_info.time_len/3600,cur_task_info.time_len/60,cur_task_info.time_len%60);
	int h,m,s;
	GetTimeFromSecs(cur_task_info.time_len,&h,&m,&s);
	cur_task_info.task_time = QTime(h,m,s);
	taskTime->display(cur_task_info.task_time.toString("hh:mm:ss"));
	taskStart();
}
void CTaskManage::taskFinish(bool isUnusual)
{
	if (/*cur_task_info.task_status != 2||*/buttonFinish->isEnabled() == false)
		return;
	else
		cur_task_info.task_status =2;

	if (dlgSimuTip)
	{
		dlgSimuTip->close();
		delete dlgSimuTip;
		dlgSimuTip = NULL;
	}
	//hide(); //DZY 14/03
	if (shm_ots_addr->simu_mode == 0)
	{
		if (!isUnusual)
		{
			saveTaskToExcel();
			QMessageBox msgBox(this);
			msgBox.setIcon(QMessageBox::Information);
			msgBox.setWindowTitle (QString::fromLocal8Bit("提示"));
			msgBox.setInformativeText(QString::fromLocal8Bit("任务已结束，是否要计算该任务得分？"));
			msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
			msgBox.setDefaultButton(QMessageBox::Ok);
			if (msgBox.exec() == QMessageBox::Ok) 
			{
				scoreDialog = new CScore(this,cur_task_info.task_id,cur_task_info.send_task_id);
				scoreDialog->setMinimumDuration(100);
				scoreDialog->exec();
				cur_task_info.score = scoreDialog->getScore();
				delete scoreDialog;
				scoreDialog = NULL;
			}
		}
		else//DZY ADDED FOR USER QIUT LOGIN
		{
// 			scoreDialog = new CScore(this,cur_task_info.task_id,cur_task_info.send_task_id);
// 			scoreDialog->setMinimumDuration(0);
// 			/*		scoreDialog->hide();*/
// 			scoreDialog->exec();
// 			/*scoreDialog->setVisible(false);*/
// 			cur_task_info.score = scoreDialog->getScore();
// 			delete scoreDialog;
// 			scoreDialog = NULL;
			cur_task_info.score = 0;
		}
	}			
	else if (shm_ots_addr->simu_mode >0)//////DZY 140619 暂时用>0代表考试竞赛等非培训模式
	{
		saveTaskToExcel();
		scoreDialog = new CScore(this,cur_task_info.task_id,cur_task_info.send_task_id);
		scoreDialog->setMinimumDuration(0);
		/*		scoreDialog->hide();*/
		scoreDialog->exec();
		/*scoreDialog->setVisible(false);*/
		cur_task_info.score = scoreDialog->getScore();
		delete scoreDialog;
		scoreDialog = NULL;
	}

	DB_FMT data;
	data.table_id = TABLE_TRAIN_INFO;
	InitDbData(&data,data.table_id);
	data.cond_flag.flag_train_info.host_id=TRUE;
	data.cond_seg.seg_train_info.host_id=g_host_id;

	data.flag.flag_train_info.status=TRUE;
	data.seg.seg_train_info.status=0;
	data.flag.flag_train_info.task_status=TRUE;
	data.seg.seg_train_info.task_status=3;
	if (UpdateOneRec(&data)!=TRUE)
	{
		HdbLogWrite(data.sql_str,data.sql_error);
		FreeDbData(&data,TABLE_TRAIN_INFO);
		return;
	}
	FreeDbData(&data,TABLE_TRAIN_INFO);
	data.table_id = TABLE_SEND_TASK;
	InitDbData(&data,data.table_id);
	data.cond_flag.flag_send_task.send_task_id = TRUE;
	data.cond_seg.seg_send_task.send_task_id = cur_task_info.send_task_id;

	data.flag.flag_send_task.score = TRUE;
	data.seg.seg_send_task.score = cur_task_info.score;
	data.flag.flag_send_task.end_time = TRUE;
	GetCurTimeStr(data.seg.seg_send_task.end_time);
	cur_task_info.end_time = QString::fromLocal8Bit(data.seg.seg_send_task.end_time);
	data.flag.flag_send_task.status = TRUE;
	if (!isUnusual)
		data.seg.seg_send_task.status = 3;
	else
		data.seg.seg_send_task.status = 4;
	//DZY 
	cur_task_info.status = data.seg.seg_send_task.status;
	if (UpdateOneRec(&data)!=TRUE)
	{
		HdbLogWrite(data.sql_str,data.sql_error);
		FreeDbData(&data,TABLE_SEND_TASK);
		return;
	}
	FreeDbData(&data,TABLE_SEND_TASK);
	if (cur_task_info.is_record == 1 ||cur_task_info.is_record == 2)
	{	
		data.table_id = TABLE_REVERT;
		InitDbData(&data,data.table_id);
		data.flag.flag_revert.revert_id =TRUE;
		data.flag.flag_revert.name=TRUE;
		data.flag.flag_revert.user_id=TRUE;
		data.flag.flag_revert.start_time=TRUE;
		data.flag.flag_revert.end_time=TRUE;
		data.flag.flag_revert.filename=TRUE;
		data.flag.flag_revert.remark=TRUE;
		data.flag.flag_revert.src=TRUE;
		data.flag.flag_revert.type=TRUE;
		data.flag.flag_revert.dev_id=TRUE;
		data.flag.flag_revert.station_id=TRUE;

		data.seg.seg_revert.revert_id = GetInexistenceIdInHdb(TABLE_REVERT);
		strcpy(data.seg.seg_revert.name,cur_task_info.task_name.toLocal8Bit().data());
		data.seg.seg_revert.user_id = login_user_id;
		strcpy(data.seg.seg_revert.start_time,cur_task_info.start_time.toLocal8Bit().data());
		strcpy(data.seg.seg_revert.end_time,cur_task_info.end_time.toLocal8Bit().data());
		strcpy(data.seg.seg_revert.filename,shm_ots_addr->dbinname);
		strcpy(data.seg.seg_revert.remark,"");
		data.seg.seg_revert.src = 0;
		data.seg.seg_revert.type = cur_task_info.is_record;
		data.flag.flag_revert.station_id = cur_task_info.stn_id;
		data.flag.flag_revert.dev_id = cur_task_info.dev_id;
		if (InsertOneRec(&data)!=TRUE)
		{
			HdbLogWrite(data.sql_str,data.sql_error);
			FreeDbData(&data,TABLE_REVERT);
			return;
		}
		FreeDbData(&data,TABLE_REVERT);
	}
	if (isUnusual)
	{
		if (shm_ots_addr->simu_mode==0)
			listTask->setItem(listTask->findItems(cur_task_info.task_name,Qt::MatchContains).at(0)->row(),3,new QTableWidgetItem(QString::fromLocal8Bit("任务非正常结束")));
		cur_task_info.task_status = 4;
		shm_ots_addr->data_task.task_status = 4;
		labelStatus->setText(QString::fromLocal8Bit("任务非正常结束"));
	}
	else
	{
		if (shm_ots_addr->simu_mode==0)
			listTask->setItem(listTask->findItems(cur_task_info.task_name,Qt::MatchContains).at(0)->row(),3,new QTableWidgetItem(QString::fromLocal8Bit("任务已完成")));
		cur_task_info.task_status = 3;
		shm_ots_addr->data_task.task_status = 3;
		labelStatus->setText(QString::fromLocal8Bit("任务已完成"));
	}
	taskTime->display("00:00:00");
	buttonStart->setEnabled(false);
	buttonReStart->setEnabled(true);
	buttonFinish->setEnabled(false);
	timerTaskTime->stop();
	emit sigTaskTimeChanged(QTime(0,0,0));
	emit sigTaskFinished();
	clearCurTask();//DZY
}
void CTaskManage::setCurTask()
{
	if (shm_ots_addr->simu_mode != 0)
	{
		PopupMessageBox(this,"当前模式任务完成后不可重新开始",QMessageBox::Information);
		return;
	}
	if (!selectionModel->hasSelection())
	{
		PopupMessageBox(this,"请选中一条任务!",QMessageBox::Information,false);
		return;
	}
	TASK_INFO task_info;
	task_info = listTask->item(listTask->currentRow(),0)->data(Qt::UserRole).value<TASK_INFO>();
	if (task_info.send_task_id == cur_task_info.send_task_id)
		return;//选中的任务是当前任务
	if (cur_task_info.task_status == 2)
	{
		QMessageBox msgBox(this);
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setWindowTitle (QString::fromLocal8Bit("警告"));
		msgBox.setInformativeText(QString::fromLocal8Bit("当前任务正在进行中，如果设置本任务为当前任务，正在执行任务会强制停止，请确认!"));
		msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Ok);
		int ret = msgBox.exec();
		if (ret == QMessageBox::Cancel) 
		{
			return;
		}
		else
		{
			taskFinish(true);
			QMessageBox msgBox(this);
			msgBox.setIcon(QMessageBox::Information);
			msgBox.setWindowTitle (QString::fromLocal8Bit("提示"));
			msgBox.setInformativeText(QString::fromLocal8Bit("任务重新启动，将删除之前该任务操作记录，是否重启该任务？"));
			msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
			msgBox.setDefaultButton(QMessageBox::Ok);
			if (msgBox.exec() == QMessageBox::Cancel) 
			{
				return;
			}
			else
			{	
				setCurTaskInfo(&task_info);
				DB_FMT data;
				data.table_id = TABLE_RECORD;
				InitDbData(&data,data.table_id);
				data.cond_flag.flag_record.send_task_id=TRUE;
				data.cond_seg.seg_record.send_task_id=task_info.send_task_id;
				DeleteOneRec(&data);
				return;
			}
		}
	}
	else
	{
		QMessageBox msgBox(this);
		msgBox.setIcon(QMessageBox::Information);
		msgBox.setWindowTitle (QString::fromLocal8Bit("提示"));
		msgBox.setInformativeText(QString::fromLocal8Bit("任务重新启动，将删除之前该任务操作记录，是否重启该任务？"));
		msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Ok);
		if (msgBox.exec() == QMessageBox::Cancel) 
		{
			return;
		}
		else
		{	
			setCurTaskInfo(&task_info);
			DB_FMT data;
			data.table_id = TABLE_RECORD;
			InitDbData(&data,data.table_id);
			data.cond_flag.flag_record.send_task_id=TRUE;
			data.cond_seg.seg_record.send_task_id=task_info.send_task_id;
			DeleteOneRec(&data);
			return;
		}
	}
}
void CTaskManage::setCurTaskInfo(TASK_INFO *task_info)
{
	cur_task_info = *task_info;
	if (shm_ots_addr->simu_mode != 0&&cur_task_info.task_grp_id<10)
	{
		labelTaskName->setText(QString::fromLocal8Bit("某操作任务"));
	}
	else
		labelTaskName->setText(cur_task_info.task_name);
	if (cur_task_info.type == 1)
		labelTaskAttr->setText(QString::fromLocal8Bit("正常操作"));
	else if (cur_task_info.type == 2)
		labelTaskAttr->setText(QString::fromLocal8Bit("故障处理"));
	labelSendTime->setText(cur_task_info.send_time);
	labelStation->setText(cur_task_info.stn_name);
	labelDev->setText(cur_task_info.dev_name);
	if (cur_task_info.task_status == 0)
		labelStatus->setText(QString::fromLocal8Bit("任务未接收"));
	else if (cur_task_info.task_status == 1)
		labelStatus->setText(QString::fromLocal8Bit("任务已接收"));
	else if (cur_task_info.task_status == 2)
		labelStatus->setText(QString::fromLocal8Bit("任务已启动"));
	else if (cur_task_info.task_status == 3)
		labelStatus->setText(QString::fromLocal8Bit("任务已完成"));
	else if (cur_task_info.task_status == 4)
		labelStatus->setText(QString::fromLocal8Bit("任务非正常结束"));
	labelScene->setText(cur_task_info.scene_name);
	if (shm_ots_addr->simu_mode != 0&&cur_task_info.task_grp_id<10)
	{
		labelFault->setText(QString::fromLocal8Bit("某故障"));
	}
	else
		labelFault->setText(cur_task_info.fault_name);
	textTaskTip->setText(cur_task_info.task_tip);
	if (cur_task_info.task_status == 1)
	{
		buttonStart->setEnabled(true);
		buttonReStart->setEnabled(false);
		buttonFinish->setEnabled(false);
	}
	else if (cur_task_info.task_status == 2)
	{
		buttonStart->setEnabled(false);
		buttonReStart->setEnabled(true);
		buttonFinish->setEnabled(true);
	}
	else if (cur_task_info.task_status == 3 || cur_task_info.task_status == 4)
	{
		buttonStart->setEnabled(false);
		buttonReStart->setEnabled(true);
		buttonFinish->setEnabled(false);
	}
	int h,m,s;
	GetTimeFromSecs(cur_task_info.time_len,&h,&m,&s);
	cur_task_info.task_time = QTime(h,m,s);
	taskTime->display(cur_task_info.task_time.toString("hh:mm:ss"));
	emit sigTaskTimeChanged(cur_task_info.task_time);
}
void CTaskManage::delTask()
{
	if (shm_ots_addr->simu_mode>0)
	{
		return;
	}
	if (!selectionModel->hasSelection())
	{
		PopupMessageBox(this,"请选中一条任务!",QMessageBox::Information,false);
		return;
	}

	int send_task_id = listTask->item(listTask->currentRow(),0)->data(Qt::UserRole).value<TASK_INFO>().send_task_id;
	if (send_task_id == cur_task_info.send_task_id && cur_task_info.task_status == 2)
	{
		QMessageBox msgBox(this);
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setWindowTitle (QString::fromLocal8Bit("警告"));
		msgBox.setInformativeText(QString::fromLocal8Bit("当前删除任务正在进行中，如果删除任务会强制停止，请确认!"));
		msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Ok);
		int ret = msgBox.exec();
		if (ret == QMessageBox::Cancel) 
		{
			return;
		}
		taskFinish(true);
		clearCurTask();
		listTask->removeRow(listTask->currentRow());
	}
	else if (send_task_id == cur_task_info.send_task_id && cur_task_info.task_status != 2)
	{
		clearCurTask();
		listTask->removeRow(listTask->currentRow());
	}
	else
		listTask->removeRow(listTask->currentRow());
	task_num--;
}
void CTaskManage::clearTaskList()
{
	if (shm_ots_addr->simu_mode>0)
	{
		return;
	}
	if(listTask->rowCount()<1)
	{
		return;
	}
	if (cur_task_info.task_status == 2)
	{
		QMessageBox msgBox(this);
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setWindowTitle (QString::fromLocal8Bit("警告"));
		msgBox.setInformativeText(QString::fromLocal8Bit("当前有任务正在进行中，如果清空任务当前任务会强制停止，请确认!"));
		msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Ok);
		int ret = msgBox.exec();
		if (ret == QMessageBox::Cancel) 
		{
			return;
		}
		taskFinish(true);
		clearCurTask();
		listTask->clear();
	}
	else
	{
		clearCurTask();
		listTask->clear();
	}
	listTask->setRowCount(0);//dzy
	task_num = 0;
}
void CTaskManage::addTask(TASK_INFO *task_info)
{
	if(shm_ots_addr->simu_mode>0)
		return;
	TASK_INFO m_task_info;
	m_task_info = *task_info;
	QVariant varTaskInfo;
	int row = listTask->rowCount();
	//DZY ADDED
	for(int i = 0 ;i<row;i++)
	{
		QString trsname = listTask->item(i,0)->text();
		if (trsname == m_task_info.task_name)
		{		
			switch(m_task_info.task_status)
			{
				case 0:
					listTask->setItem(i,3,new QTableWidgetItem(QString::fromLocal8Bit("任务未接收")));
					break;
				case 1:
					listTask->setItem(i,3,new QTableWidgetItem(QString::fromLocal8Bit("任务已接收")));
					break;
				case 2:
					listTask->setItem(i,3,new QTableWidgetItem(QString::fromLocal8Bit("任务已启动")));
					break;
				case 3:
					listTask->setItem(i,3,new QTableWidgetItem(QString::fromLocal8Bit("任务已完成")));
					break;
				case 4:
					listTask->setItem(i,3,new QTableWidgetItem(QString::fromLocal8Bit("任务非正常结束")));
					break;
				default:
					break;
			}
			return;
		}
	}
	listTask->setRowCount(row);
	listTask->insertRow(row);
	QTableWidgetItem *item = new QTableWidgetItem(m_task_info.task_name);
	varTaskInfo.setValue(m_task_info);
	item->setData(Qt::UserRole,varTaskInfo);

	listTask->setItem(row,0,item);
	listTask->setItem(row,1,new QTableWidgetItem(m_task_info.send_time));
	listTask->setItem(row,2,new QTableWidgetItem(QString::number(m_task_info.time_len)));
	switch(m_task_info.task_status)
	{
		case 0:
			listTask->setItem(row,3,new QTableWidgetItem(QString::fromLocal8Bit("任务未接收")));
			break;
		case 1:
			listTask->setItem(row,3,new QTableWidgetItem(QString::fromLocal8Bit("任务已接收")));
			break;
		case 2:
			listTask->setItem(row,3,new QTableWidgetItem(QString::fromLocal8Bit("任务已启动")));
			break;
		case 3:
			listTask->setItem(row,3,new QTableWidgetItem(QString::fromLocal8Bit("任务已完成")));
			break;
		case 4:
			listTask->setItem(row,3,new QTableWidgetItem(QString::fromLocal8Bit("任务非正常结束")));
			break;
		default:
			break;
	}
	task_num++;
}
bool CTaskManage::isCurTaskRun()
{
	//return false;
	if (cur_task_info.task_status != 2)
		return false;
	else
		return true;
}
int CTaskManage::taskNum()
{
	return task_num;
}
void CTaskManage::getCurTaskInfo(TASK_INFO *task_info)
{
	*task_info = cur_task_info;
}
void CTaskManage::taskTimeCountDown()
{
	cur_task_info.task_time = cur_task_info.task_time.addSecs(-1);
	taskTime->display(cur_task_info.task_time.toString("hh:mm:ss"));
	emit sigTaskTimeChanged(cur_task_info.task_time);
	if (cur_task_info.task_time == QTime(0,0,0))
	{
		timerTaskTime->stop();
		emit sigTimeOut();
	}
}
void CTaskManage::timeOut()
{
	PopupMessageBox(this,"当前任务时间已到!",QMessageBox::Information,false);
	taskFinish(false);//DZY NEW ADDED 任务时间到了正常评分
}
void CTaskManage::switchSimuTip(int state)
{
	if (state == Qt::Checked)
	{
		if (dlgSimuTip!=NULL)
			dlgSimuTip->show();
	}
	if (state == Qt::Unchecked)
	{
		if (dlgSimuTip!=NULL)
			dlgSimuTip->hide();
	}
}
void CTaskManage::saveTaskToExcel()
{
	QDialog *dialog = new QDialog(this);
	QGridLayout *layout = new QGridLayout(dialog);
	QLabel *label = new QLabel(dialog);
	QCheckBox *checkAlarm = new QCheckBox(dialog);
	QCheckBox *checkCmd = new QCheckBox(dialog);
	QCheckBox *checkOpr = new QCheckBox(dialog);
	QCheckBox *checkCheck = new QCheckBox(dialog);
	QPushButton *buttonSave = new QPushButton(dialog);
	QPushButton *buttonCancel = new QPushButton(dialog);
	//dialog->setAttribute(Qt::WA_DeleteOnClose);
	dialog->setWindowTitle(QString::fromLocal8Bit("保存任务操作"));
	label->setText(QString::fromLocal8Bit("如果要保存任务操作为EXCEL文件，请选择要保存的操作类型后点保存，否则请取消。"));
	label->setWordWrap(true);
	checkAlarm->setText(QString::fromLocal8Bit("报警记录"));
	checkCmd->setText(QString::fromLocal8Bit("命令下达"));
	checkCmd->setCheckState(Qt::Checked);
	checkOpr->setText(QString::fromLocal8Bit("现地操作"));
	checkOpr->setCheckState(Qt::Checked);
	checkCheck->setText(QString::fromLocal8Bit("设备检查"));
	checkCheck->setCheckState(Qt::Checked);
	buttonSave->setText(QString::fromLocal8Bit("保存"));
	buttonCancel->setText(QString::fromLocal8Bit("取消"));
	layout->addWidget(label, 0, 0, 1, 2);
	layout->addWidget(checkAlarm, 1, 0, 1, 2);
	layout->addWidget(checkCmd, 2, 0, 1, 2);
	layout->addWidget(checkOpr, 3, 0, 1, 2);
	layout->addWidget(checkCheck, 4, 0, 1, 2);
	layout->addWidget(buttonSave, 5, 0, 1, 1);
	layout->addWidget(buttonCancel, 5, 1, 1, 1);
	connect(buttonSave,SIGNAL(clicked()),dialog,SLOT(accept()));
	connect(buttonCancel,SIGNAL(clicked()),dialog,SLOT(reject()));
	if (dialog->exec() == QDialog::Rejected)
		return;

	QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
		tr("Excel Files (*.xls)"));
	if (fileName.isEmpty())
		return;
	DB_FMT data;
	InitDbData(&data,TABLE_RECORD);
	data.cond_flag.flag_record.send_task_id = TRUE;
	data.cond_seg.seg_record.send_task_id = cur_task_info.send_task_id;
	if( SelectRecs(&data) != TRUE)
	{
		HdbLogWrite(data.sql_str,data.sql_error);
		return;
	}
	ExcelObjectODBC excel(fileName,"sheet");
	excel.AddHeader(0, "CODE", "char(5)");
	excel.AddHeader(1, "NAME", "char(100)");
	excel.AddHeader(2, "TYPE", "char(10)");
	excel.AddHeader(3, "LOGICALNAME","char(38)");
	excel.AddHeader(4, "TYPE_ID", "int");
	excel.AddHeader(5, "STATUS", "int");
	excel.AddHeader(6, "FVALUE", "int");
	excel.AddHeader(7, "SCORE", "int");
	excel.AddHeader(8, "IS_KEYSTEP", "int");
	if (excel.Open())
	{
		QVariantList rowValues;
		QString typeStr;
		for (int i=data.rownum-1;i>=0;i--)
		{
			if (data_record[i].type == 2)
				continue;
			if (checkAlarm->checkState() == Qt::Unchecked && data_record[i].type == 1)
				continue;
			if (checkCmd->checkState() == Qt::Unchecked && data_record[i].type == 0)
				continue;
			if (checkOpr->checkState() == Qt::Unchecked && data_record[i].type == 3)
				continue;
			if (checkCheck->checkState() == Qt::Unchecked && data_record[i].type == 4)
				continue;
			if (data_record[i].type == 0) typeStr = "CMD";
			else if (data_record[i].type == 1) typeStr = "ALARM";
			else if (data_record[i].type == 3) typeStr = "OPR";
			else if (data_record[i].type == 4) typeStr = "CHECK";

			rowValues.clear();
			rowValues.append(QVariant("STEP"));
			rowValues.append(QVariant(data_record[i].content));
			rowValues.append(QVariant(typeStr));
			rowValues.append(QVariant(data_record[i].logicalname));
			rowValues.append(QVariant(data_record[i].type_id));
			rowValues.append(QVariant(data_record[i].status));
			rowValues.append(QVariant(data_record[i].fvalue));
			rowValues.append(QVariant(0));
			rowValues.append(QVariant(0));
			excel.WriteRow(rowValues);
		}
	}
	dialog->deleteLater();
}
void CTaskManage::displayTaskRec(int index)
{
	if (index==2)
	{
		if(shm_ots_addr->simu_mode>0)
			return;
		DB_FMT data;
		InitDbData(&data,TABLE_SEND_TASK);
		data.cond_flag.flag_send_task.user_id = TRUE;
		data.cond_seg.seg_send_task.user_id = login_user_id;
		if( SelectRecs(&data) != TRUE)
		{		
			HdbLogWrite(data.sql_str,data.sql_error);
			qDebug("查询数据库失败!");
			return;
		}
		listTaskRec->clearContents();
		listTaskRec->setRowCount(data.rownum);
		int rownum = data.rownum;
		for(int i=0;i<rownum;i++)
		{		
			QTableWidgetItem* itemTaskName = new QTableWidgetItem(QString::fromLocal8Bit(data_send_task[i].task_name));
			itemTaskName->setData(Qt::UserRole,data_send_task[i].send_task_id);
			itemTaskName->setData(Qt::UserRole+1,QString::fromLocal8Bit(data_send_task[i].send_time));
			itemTaskName->setData(Qt::UserRole+2,QString::fromLocal8Bit(data_send_task[i].start_time));
			itemTaskName->setData(Qt::UserRole+3,QString::fromLocal8Bit(data_send_task[i].end_time));
			listTaskRec->setItem(i,0,itemTaskName);
			listTaskRec->setItem(i,1,new QTableWidgetItem(QString::number(data_send_task[i].score)));
		}	
		return;
	}
	else if (index==3)
	{
		DB_FMT data,data2;
		InitDbData(&data,TABLE_STUDY_PLAN);
		InitDbData(&data2,TABLE_STUDY_RECORD);
		data.cond_flag.flag_study_plan.user_type_id = TRUE;
		data.cond_seg.seg_study_plan.user_type_id = login_user_type;

		if( SelectRecs(&data) != TRUE)
		{		
			HdbLogWrite(data.sql_str,data.sql_error);
			qDebug("查询数据库失败!");
			return;
		}
		tablePlan->clearContents();
		tablePlan->setRowCount(data.rownum);
		int rownum = data.rownum;
		for(int i=0;i<rownum;i++)
		{		
			QTableWidgetItem* itemStudyPlan = new QTableWidgetItem(QString::fromLocal8Bit(data_study_plan[i].name));
			itemStudyPlan->setData(Qt::UserRole,data_study_plan[i].plan_id);
			itemStudyPlan->setData(Qt::UserRole+1,QString::number(data_study_plan[i].doc_id));
			itemStudyPlan->setData(Qt::UserRole+2,QString::number(data_study_plan[i].task_id));
			data2.cond_flag.flag_study_record.plan_id = true;
			data2.cond_seg.seg_study_record.plan_id = data_study_plan[i].plan_id;
			data2.cond_flag.flag_study_record.user_id = true;
			data2.cond_seg.seg_study_record.user_id = login_user_id;
			if( SelectRecs(&data2) != TRUE)
			{		
				HdbLogWrite(data2.sql_str,data.sql_error);
				qDebug("查询数据库失败!");
				continue;
			}
			QTableWidgetItem* itemStudyPlan1 = new QTableWidgetItem(QString::number(data_study_record[0].points));
/*			itemStudyPlan->setData(Qt::UserRole+3,QString::fromLocal8Bit(data_send_task[i].end_time));*/
			tablePlan->setItem(i,0,itemStudyPlan);
			tablePlan->setItem(i,1,itemStudyPlan1);
			tablePlan->setItem(i,2,new QTableWidgetItem(QString::number(data_study_plan[i].study_points)));
		}	
		return;
	}
}
void CTaskManage::PopupTaskRecDetail(const QModelIndex &index)
{
	QString send_time,start_time,end_time;
	send_time = listTaskRec->item(index.row(),0)->data(Qt::UserRole+1).toString();
	start_time = listTaskRec->item(index.row(),0)->data(Qt::UserRole+2).toString();
	end_time = listTaskRec->item(index.row(),0)->data(Qt::UserRole+3).toString();
	QString text = QString::fromLocal8Bit("发送时间:%1").arg(send_time)
		+QString::fromLocal8Bit("<br>开始时间:%1").arg(start_time)
		+QString::fromLocal8Bit("<br>结束时间:%1").arg(end_time);
	QToolTip::showText(QCursor::pos(), text, this);
}

void  CTaskManage::onexit()
{

	if (shm_ots_addr->data_task.task_status==2)
	{
		taskFinish(true);
	}
	emit closedlg();
	//this->close();
}
/********************************************************************CNewTaskTip***************************************************************************/
CNewTaskTip::CNewTaskTip(QWidget *parent)
: QWidget(parent,Qt::WindowStaysOnTopHint | Qt::Tool | Qt::X11BypassWindowManagerHint)//没有窗口边框 不在任务栏显示
{
	setupUi();
	setAttribute(Qt::WA_DeleteOnClose);
	dlg_created_flag[NEWTASKARVDLG] = true;
	timer = new QTimer;
	connect(buttonSetCurTask,SIGNAL(clicked()),this,SLOT(setCurTask()));
	connect(buttonAddTaskList,SIGNAL(clicked()),this,SLOT(addTaskList()));
	connect(buttonIgnoreTask,SIGNAL(clicked()),this,SLOT(ignoreTask()));
	connect(timer,SIGNAL(timeout()),this,SLOT(updateTitle()));
}
CNewTaskTip::~CNewTaskTip()
{
	dlg_created_flag[NEWTASKARVDLG] = false;
}

void CNewTaskTip::showEvent(QShowEvent *event)
{
	flagTitle = false;
	timer->start(1000);
	//DZY 140704MODIFIED 
	if (shm_ots_addr->simu_mode != 0&&m_task_info.task_grp_id<10)
	{
		labelTaskName->setText(QString::fromLocal8Bit("某操作任务"));
		labelTip->setText(QString::fromLocal8Bit("提示:")+m_task_info.task_tip);
	}
	else
		labelTaskName->setText(m_task_info.task_name);
	//labelTaskName->setText(m_task_info.task_name);
	labelTaskTime->setText(QString::fromLocal8Bit("时限：%1分钟").arg(m_task_info.time_len/60));
	if (taskManage->taskNum() == 0)
		buttonAddTaskList->setEnabled(false);
	event->accept();
}
void CNewTaskTip::closeEvent(QCloseEvent *event)
{
	ignoreTask();
	//DZY
	disconnect(buttonSetCurTask,SIGNAL(clicked()),this,SLOT(setCurTask()));
	disconnect(buttonAddTaskList,SIGNAL(clicked()),this,SLOT(addTaskList()));
	disconnect(buttonIgnoreTask,SIGNAL(clicked()),this,SLOT(ignoreTask()));

	event->accept();
}
void CNewTaskTip::paintEvent(QPaintEvent *event)
{
// 	QPainter painter(this);
// 	painter.fillRect(event->rect(), QBrush(Qt::yellow));
// 	painter.setPen(QPen(Qt::red));
// 	painter.drawRect(event->rect().x(),event->rect().y(),event->rect().width()-1,event->rect().height()-1);
}
void CNewTaskTip::setupUi()
{
	mainLayout = new QGridLayout;
	labelTitle = new QLabel(this);
	labelTaskName = new QLabel(this);
	labelTaskTime = new QLabel(this);
	buttonSetCurTask = new QPushButton(this);
	buttonAddTaskList = new QPushButton(this);
	buttonIgnoreTask = new QPushButton(this);
	labelTip = new QLabel(this);
	QHBoxLayout *hlayout = new QHBoxLayout;
	//QPalette palette;
	//palette.setBrush(QPalette::BackgrouAnd,QBrush(Qt::yellow));
	//labelTaskName->setPalette(palette);
	//buttonSetCurTask->setMinimumHeight(51);
	//buttonAddTaskList->setMinimumHeight(51);
	//buttonIgnoreTask->setMinimumHeight(51);
	QFont font(QString::fromLocal8Bit("华文行楷"), 22, QFont::Bold);
	//buttonSetCurTask->setStyleSheet("background-color: rgb(158, 217, 255);");
	//buttonAddTaskList->setStyleSheet("background-color: rgb(158, 217, 255);");
	//buttonIgnoreTask->setStyleSheet("background-color: rgb(158, 217, 255);");
	labelTitle->setText(QString::fromLocal8Bit("收     到     新     任     务"));
	labelTitle->setFont(font);
	//QPalette pat;
	//pat.setColor(QPalette::Background,QColor(255,255,0));
	//pat.setBrush(QPalette::Background,QBrush(QColor(255,255,0)));
	//setPalette(pat);
	labelTaskName->setStyleSheet("font: 16pt");
	labelTaskName->setWordWrap(true);
	labelTaskName->setAlignment(Qt::AlignCenter);
	labelTaskName->setScaledContents(true);
	labelTaskName->setMargin(0);

	labelTip->setStyleSheet("font: 12pt");
	labelTip->setWordWrap(true);
	labelTip->setAlignment(Qt::AlignCenter);
	labelTip->setScaledContents(true);
	labelTip->setMargin(0);

	labelTaskTime->setStyleSheet("font: 14pt");
	hlayout->addWidget(buttonSetCurTask,2);
	hlayout->addWidget(buttonAddTaskList,2);
	hlayout->addWidget(buttonIgnoreTask,2);
	mainLayout->setContentsMargins(1,1,1,1);
 	mainLayout->addWidget(labelTitle,0,0,1,2,Qt::AlignTop | Qt::AlignHCenter);
 	mainLayout->addWidget(labelTaskName,1,0,1,2,Qt::AlignCenter);
 	mainLayout->addWidget(labelTaskTime,2,0,1,2,Qt::AlignBottom | Qt::AlignHCenter);
	mainLayout->addWidget(labelTip,3,0,1,2,Qt::AlignBottom | Qt::AlignHCenter);
 	mainLayout->addLayout(hlayout,4,0,1,2,Qt::AlignBottom);
	buttonSetCurTask->setText(QString::fromLocal8Bit("执行此任务"));
	buttonAddTaskList->setText(QString::fromLocal8Bit("添加到任务队列"));
	buttonIgnoreTask->setText(QString::fromLocal8Bit("忽略此任务"));
	setLayout(mainLayout);
	resize(400,300);
}
void CNewTaskTip::updateTitle()
{
	if (flagTitle)
	{
		labelTitle->setStyleSheet("");
		flagTitle = false;
	}
	else
	{
		labelTitle->setStyleSheet("background-color: rgb(255, 0, 0);");
		flagTitle = true;
	}
	
}
void CNewTaskTip::setTaskInfo(TASK_INFO *task_info)
{
	m_task_info = *task_info;
}
void CNewTaskTip::setCurTask()
{
	if (taskManage->isCurTaskRun() == true)
	{
		QMessageBox msgBox(this);
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setWindowTitle (QString::fromLocal8Bit("警告"));
		msgBox.setInformativeText(QString::fromLocal8Bit("当前任务正在进行中，如果继续当前任务会强制停止并替换为本次设置的任务，请确认!"));
		msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Ok);
		int ret = msgBox.exec();
		if (ret == QMessageBox::Cancel) 
		{
			return;
		}
		taskManage->taskFinish(true);
 		taskManage->addTask(&m_task_info);
		taskManage->setCurTaskInfo(&m_task_info);

		//dzy
		this->close();
	}
	else
	{
		//taskManage->cur_task_info.task_status = 1;
		taskManage->taskFinish(true);
		taskManage->addTask(&m_task_info);
		taskManage->setCurTaskInfo(&m_task_info);
//		taskManage->show();
		emit sig_taskaccepted();
	}
	taskManage->tabWidget->setCurrentIndex(0);
	//taskManage->show();
	shm_ots_addr->data_task.task_status = 1;
	close();
}
void CNewTaskTip::addTaskList()
{
	taskManage->addTask(&m_task_info);
	shm_ots_addr->data_task.task_status = 1;
	close();
}
void CNewTaskTip::ignoreTask()
{
	shm_ots_addr->data_task.task_status = 1;
	close();
}
/*******************************************************************************************************************************************/
CScore::CScore(QWidget *parent,int task_id,int send_task_id) 
: QDialog(parent)
{
	qApp->setStyleSheet("");
	m_task_id = task_id;
	m_send_task_id = send_task_id;
	waitDialog = NULL;
	resultDialog = NULL;
	detailDialog = NULL;
	calcTimer = new QTimer;
	showTimer = new QTimer;
	labelWait = new QLabel(this);
	buttonWait = new QPushButton(this);
	buttonDetail = new QPushButton(this);
	buttonExit = new QPushButton(this);
	showTime = 1000;
	calcTimer->setSingleShot(true);
	showTimer->setSingleShot(true);
	labelWait->setStyleSheet(QString::fromLocal8Bit("QLabel{color: rgb(255, 0, 0);font: 75 40pt 楷体;}"));
	buttonWait->setStyleSheet(QString::fromLocal8Bit("border-image: url(:pic/images/继续等待.png);"));
	buttonDetail->setStyleSheet(QString::fromLocal8Bit("border-image: url(:pic/images/查看详情.png);"));
	buttonExit->setStyleSheet(QString::fromLocal8Bit("border-image: url(:pic/images/退出.png);"));
	buttonWait->setMinimumSize(198,142);
	buttonDetail->setMinimumSize(198,142);
	buttonExit->setMinimumSize(198,142);
	buttonWait->setCursor(QCursor(Qt::PointingHandCursor));
	buttonDetail->setCursor(QCursor(Qt::PointingHandCursor));
	buttonExit->setCursor(QCursor(Qt::PointingHandCursor));
	QSpacerItem *verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
	QSpacerItem *horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
	QHBoxLayout *hlayout = new QHBoxLayout;
	QVBoxLayout *vlayout = new QVBoxLayout;
	QVBoxLayout *layout = new QVBoxLayout(this);
	vlayout->addWidget(buttonWait);
	vlayout->addWidget(buttonDetail);
	vlayout->addWidget(buttonExit);
	hlayout->addSpacerItem(horizontalSpacer);
	hlayout->addLayout(vlayout);
	layout->addWidget(labelWait,Qt::AlignCenter);
	layout->addSpacerItem(verticalSpacer);
	layout->addLayout(hlayout);
	//setAttribute(Qt::WA_DeleteOnClose);
	setWindowOpacity(1.0);
	setAttribute(Qt::WA_TranslucentBackground, true);
	QRect rect = QApplication::desktop()->screenGeometry(QApplication::desktop()->screenNumber(this));
	resize(rect.size());
	if (ConnectHDB(db_calc,"calc"))
		calc = new CTaskCalculation(m_task_id,m_send_task_id,db_calc); 
	else
		calc = new CTaskCalculation(m_task_id,m_send_task_id,db_conn); 
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool | Qt::X11BypassWindowManagerHint);
	calcScoreThread = new CalcScoreThread(calc,this);
	connect(buttonWait,SIGNAL(clicked()),this,SLOT(showWaitDialog()));
	connect(showTimer,SIGNAL(timeout()),this,SLOT(showWaitDialog()));
	connect(calcScoreThread,SIGNAL(finished()),this,SLOT(showResultDialog()));
	connect(buttonDetail,SIGNAL(clicked()),this,SLOT(showDetailDialog()));
	connect(buttonExit,SIGNAL(clicked()),this,SLOT(close()));
	connect(calcTimer,SIGNAL(timeout()),this,SLOT(timeOut()));
}
CScore::~CScore()
{
	QFile file(":/pic/qss/default.qss");
	file.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(file.readAll());
	qApp->setStyleSheet(styleSheet);
	delete waitDialog;
	delete resultDialog;
	delete detailDialog;
	waitDialog = NULL;
	resultDialog = NULL;
	detailDialog = NULL;
	calcTimer->stop();
	if (calcScoreThread->isRunning())
	{
		calcScoreThread->terminate();
		calcScoreThread->wait();
		calcScoreThread->quit();
	}
	CloseHDB(db_calc);
}
void CScore::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.fillRect(event->rect(), QColor(0,0,0,200));
}
void CScore::loadChinese()
{
	QTranslator translator;
	translator.load("SimuTrainee_zh_CN");
	qApp->installTranslator(&translator);
	translateLanguage();
}
void CScore::loadEnglish()
{
	QTranslator translator;
	translator.load("SimuTrainee_en");
	qApp->installTranslator(&translator);
	translateLanguage();
}
void CScore::translateLanguage()
{
// 	title_label->setText(tr("title"));
// 	title_info_label->setText(tr("360 safe"));
// 	info_label->setText(tr("info"));
// 	version_label->setText(tr("version") + QString("9.2.0.2001"));
// 	mummy_label->setText(tr("mummy") + QString("2013-10-14"));
// 	copyright_label->setText(tr("copyright"));
// 	close_button->setToolTip(tr("close"));
// 	ok_button->setText(tr("ok"));
}
void CScore::showEvent(QShowEvent *event)
{
// 	if (flag_langueage == 0)
// 	{
// 		loadChinese();
// 	}
// 	else if (flag_langueage == 1)
// 	{
// 		loadEnglish();
// 	}
	calcTimer->start(60000);
	calcScoreThread->start();
	showTimer->start(showTime);
	event->accept();
}
void CScore::creatWaitDialog()
{
	waitDialog = new QWidget(this,Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool | Qt::X11BypassWindowManagerHint);
	waitDialog->setAttribute(Qt::WA_DeleteOnClose);
	waitDialog->setAttribute(Qt::WA_TranslucentBackground, true);
	//waitDialog->setStyleSheet("");
	QMovie *movie = new QMovie(waitDialog);
	movie->setFileName(QString::fromLocal8Bit(":/pic/images/wait.gif"));
	QLabel *label = new QLabel(waitDialog);
	QLabel *labelMovie = new QLabel(waitDialog);
	labelMovie->setMovie(movie);
	movie->setSpeed(80);
	movie->start();
	QFont f_label(QString::fromLocal8Bit("华文行楷"), 50, QFont::Bold);
	label->setText(QString::fromLocal8Bit("任务得分正在计算中，\n      请耐心等待结果哦"));
	QPalette p_label;
	p_label.setColor(QPalette::WindowText,Qt::white);
	label->setPalette(p_label);
	label->setFont(f_label);
	QGridLayout *layout = new QGridLayout(waitDialog);
	layout->addWidget(label,0,0,Qt::AlignCenter);
	layout->addWidget(labelMovie,1,0,Qt::AlignCenter);
	QRect rect = QApplication::desktop()->screenGeometry(QApplication::desktop()->screenNumber(this));
	waitDialog->resize(rect.size());
}
void CScore::creatResultDialog()
{
	score = calc->getTaskScore();
	if (shm_ots_addr->simu_mode>0)
	{
		return;
	}
	resultDialog = new QWidget(this,Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool | Qt::X11BypassWindowManagerHint);
	resultDialog->setAttribute(Qt::WA_DeleteOnClose);
	resultDialog->setAttribute(Qt::WA_TranslucentBackground, true);
	//	resultDialog->setStyleSheet("");
	QLabel *lableScore = new QLabel(resultDialog);
	QLabel *lableScoreTip = new QLabel(resultDialog);
	QLabel *labelImage = new QLabel(resultDialog);
	QMovie *movie = new QMovie(resultDialog);
	QGridLayout *layout = new QGridLayout(resultDialog);	
	QTimer *timer = new QTimer(resultDialog);
	QPalette p_label,p_labeltip;
	QSize imageSize(200,200);
	QFont f_label(QString::fromLocal8Bit("华文行楷"), 120, QFont::Bold);
	QFont f_labeltip(QString::fromLocal8Bit("华文行楷"), 120, QFont::Bold);
	//layout->setSizeConstraint(QLayout::SetFixedSize);
	lableScoreTip->setText(QString::fromLocal8Bit("本任务得分"));
	lableScore->setText(QString::number(score)+QString::fromLocal8Bit(" 分"));
// 	lableScoreTip->setStyleSheet(QString::fromLocal8Bit("QLabel{color: rgb(0, 0, 255);font: 16pt 宋体;}"));
 	lableScore->setStyleSheet(QString::fromLocal8Bit("QLabel{color: rgb(0, 0, 255);font: 16pt 宋体;}"));
	p_label.setColor(QPalette::WindowText,Qt::yellow);
	p_labeltip.setColor(QPalette::WindowText, Qt::blue);
	lableScore->setPalette(p_label);
	lableScore->setFont(f_label);
	lableScoreTip->setPalette(p_labeltip);
	lableScoreTip->setFont(f_labeltip);
	labelImage->setMovie(movie);
	movie->setScaledSize(imageSize);
	int m_iScore = score/10;
	switch(m_iScore)
	{
		case 10 :
			movie->setFileName(QString::fromLocal8Bit(":/pic/images/酷.gif"));
			break;
		case 9 :
		case 8 :
		case 7 :
		case 6 :
			movie->setFileName(QString::fromLocal8Bit(":/pic/images/酷.gif"));
			break;
		case 5 :
		case 4 :
		case 3 :
		case 2 :
		case 1 :
			movie->setFileName(QString::fromLocal8Bit(":/pic/images/哭.gif"));
			break;
		case 0 :
			movie->setFileName(QString::fromLocal8Bit(":/pic/images/打.gif"));
			break;
	}
	movie->setSpeed(80);
	movie->start();
	layout->addWidget(labelImage,0,0,Qt::AlignCenter);
	layout->addWidget(lableScoreTip,1,0,Qt::AlignCenter);
	layout->addWidget(lableScore,2,0,Qt::AlignCenter);
	QRect rect = QApplication::desktop()->screenGeometry(QApplication::desktop()->screenNumber(this));
	resultDialog->setLayout(layout);
	resultDialog->resize(rect.size());
}
void CScore::creatDetailDialog()
{
	detailDialog = new QWidget(this,Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool | Qt::X11BypassWindowManagerHint);
	detailDialog->setAttribute(Qt::WA_DeleteOnClose);
	detailDialog->setAttribute(Qt::WA_TranslucentBackground, true);
	QRect rect = QApplication::desktop()->screenGeometry(QApplication::desktop()->screenNumber(this));
	QScrollArea *scrollArea = new QScrollArea(detailDialog);
	QWidget *scrollAreaWidgetContents = new QWidget;
	QPalette pal = scrollArea->palette(); 
	pal.setColor(QPalette::Background, QColor(0x00,0xff,0x00,0x00)); 
	scrollArea->setPalette(pal);
	scrollArea->setWidgetResizable(true);
	scrollArea->setWidget(scrollAreaWidgetContents);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setMinimumSize(rect.width()-250,rect.height());
	scrollArea->setMaximumSize(rect.width()-250,rect.height());
	QVBoxLayout *layout = new QVBoxLayout(detailDialog);
	layout->setContentsMargins(0,0,0,0);
	layout->addWidget(scrollArea);
	QVBoxLayout *slayout = new QVBoxLayout(scrollAreaWidgetContents);
	for (int i=1;i<=calc->getStepNum();i++)
	{
		QHBoxLayout *hlayout = new QHBoxLayout;
		QLabel *labelName = new QLabel(detailDialog);
		QLabel *labelStatus = new QLabel(detailDialog);
		labelName->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
		labelStatus->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
		if (calc->getStepSubjectInfo(i)->is_keystep)
			labelName->setText(QString::fromLocal8Bit("★%1 (%2分)").arg(calc->getStepSubjectInfo(i)->name).arg(calc->getStepSubjectInfo(i)->score));
		else
			labelName->setText(QString::fromLocal8Bit("  %1 (%2分)").arg(calc->getStepSubjectInfo(i)->name).arg(calc->getStepSubjectInfo(i)->score));
		if (calc->getStepStatus(i) == SUBJECT_STATUS_UNJUDGE)
		{
			labelName->setStyleSheet(QString::fromLocal8Bit("QLabel{color: rgb(0, 0, 255);font: 75 20pt 楷体;}"));
			labelStatus->setStyleSheet(QString::fromLocal8Bit("QLabel{color: rgb(0, 0, 255);font: 75 20pt 楷体;}"));
			labelStatus->setText(QString::fromLocal8Bit("未评分"));
		}		if (calc->getStepStatus(i) == SUBJECT_STATUS_FINISH)
		{
			labelName->setStyleSheet(QString::fromLocal8Bit("QLabel{color: rgb(0, 255, 0);font: 75 20pt 楷体;}"));
			labelStatus->setStyleSheet(QString::fromLocal8Bit("QLabel{color: rgb(0, 255, 0);font: 75 20pt 楷体;}"));
			labelStatus->setText(QString::fromLocal8Bit("完成"));
		}
		if (calc->getStepStatus(i) == SUBJECT_STATUS_UNFINISH)
		{
			labelName->setStyleSheet(QString::fromLocal8Bit("QLabel{color: rgb(255, 0, 0);font: 75 20pt 楷体;}"));
			labelStatus->setStyleSheet(QString::fromLocal8Bit("QLabel{color: rgb(255, 0, 0);font: 75 20pt 楷体;}"));
			labelStatus->setText(QString::fromLocal8Bit("未完成"));
		}
		if (calc->getStepStatus(i) == SUBJECT_STATUS_UNSATISFIYED)
		{
			labelName->setStyleSheet(QString::fromLocal8Bit("QLabel{color: rgb(0, 255, 255);font: 75 20pt 楷体;}"));
			labelStatus->setStyleSheet(QString::fromLocal8Bit("QLabel{color: rgb(0, 255, 255);font: 75 20pt 楷体;}"));
			labelStatus->setText(QString::fromLocal8Bit("前提条件未满足"));
		}
		if (calc->getStepStatus(i) == SUBJECT_STATUS_DISORDER)
		{
			labelName->setStyleSheet(QString::fromLocal8Bit("QLabel{color: rgb(255, 0, 255);font: 75 20pt 楷体;}"));
			labelStatus->setStyleSheet(QString::fromLocal8Bit("QLabel{color: rgb(255, 0, 255);font: 75 20pt 楷体;}"));
			labelStatus->setText(QString::fromLocal8Bit("操作次序错误"));
		}
		if (calc->getStepStatus(i) == SUBJECT_KEYBEFOREUNFINISH_BUTRIGHT)
		{
			labelName->setStyleSheet(QString::fromLocal8Bit("QLabel{color: rgb(255, 255, 0);font: 75 20pt 楷体;}"));
			labelStatus->setStyleSheet(QString::fromLocal8Bit("QLabel{color: rgb(255, 255, 0);font: 75 20pt 楷体;}"));
			labelStatus->setText(QString::fromLocal8Bit("前关键步未完本步完成但不得分"));
		}
		if (calc->getStepStatus(i) == SUBJECT_KEYBEFOREUNFINISH_ANDWRONG)
		{
			labelName->setStyleSheet(QString::fromLocal8Bit("QLabel{color: rgb(127, 0, 0);font: 75 20pt 楷体;}"));
			labelStatus->setStyleSheet(QString::fromLocal8Bit("QLabel{color: rgb(127, 0, 0);font: 75 20pt 楷体;}"));
			labelStatus->setText(QString::fromLocal8Bit("关键步未完且本步操作不正确"));
		}
		hlayout->addWidget(labelName,Qt::AlignLeft);
		hlayout->addWidget(labelStatus);
		slayout->addLayout(hlayout);
	}
	detailDialog->move(0,0);
}
void CScore::showWaitDialog()
{
	if (shm_ots_addr->simu_mode>0)
	{
		return;
	}
	buttonWait->hide();
	buttonDetail->hide();
	buttonExit->hide();
	creatWaitDialog();
	waitDialog->show();
	labelWait->clear();
}
void CScore::showResultDialog()
{
	if (shm_ots_addr->simu_mode>0)
	{
		buttonExit->click();
		calcTimer->stop();
		showTimer->stop();
		creatResultDialog();
		return;
	}
	buttonWait->hide();
	buttonDetail->show();
	buttonExit->show();
	labelWait->clear();
	calcTimer->stop();
	showTimer->stop();
	if (waitDialog)
	{
		waitDialog->close();
		waitDialog = NULL;
	}
	creatResultDialog();
	resultDialog->show();
}
void CScore::showDetailDialog()
{
	if (shm_ots_addr->simu_mode>0)
	{
		return;
	}
	buttonWait->hide();
	buttonDetail->hide();
	buttonExit->show();
	if (resultDialog)
	{
		resultDialog->close();
		resultDialog = NULL;
	}
	creatDetailDialog();
	detailDialog->show();
}
void CScore::timeOut()
{
	buttonWait->show();
	buttonDetail->hide();
	buttonExit->show();
	if (waitDialog)
	{
		waitDialog->close();
		waitDialog = NULL;
	}
	//calcScoreThread->wait();
	labelWait->setText(QString::fromLocal8Bit("得分计算等待时间超时，是否继续等待？"));
}
/****************************************************************************************************************************/
void CalcScoreThread::run()
{
	QMutexLocker locker(&mutex);
	m_calc->calcTaskScore();
}