#include "control_section.h"
#include "main_window.h"

ControlSection::ControlSection(QMainWindow *parent)
    : QWidget (parent)
{
    // set the progress bar
    progressbar = new QProgressBar(this);
    progressbar->setRange(0, 100);
    progressbar->setValue(0);
    progressbar->setOrientation(Qt::Horizontal);
    progressbar->setGeometry(125, 55, 400, 35);

    // set the result section
    result = new QLabel(this);
    result->setStyleSheet("border: 1px solid black");
    result->setGeometry(125, 120, 400, 400);

    // set the control section
    button_aggregate = new QPushButton("Aggregate", this);
    button_start_cancel = new QPushButton("Start", this);
    button_pause_resume = new QPushButton("Pause", this);

    button_start_cancel->setEnabled(true);
    button_pause_resume->setEnabled(false);

    button_aggregate->setGeometry(280, 592, 90, 30);
    button_start_cancel->setGeometry(155, 650, 90, 30);
    button_pause_resume->setGeometry(405, 650, 90, 30);

    // initialization of assistant, datasaver and classifier
    MainWindow *m_main_window = parent;
    assistant = m_main_window->getAssistant();
    datasaver = m_main_window->getDataSaver();
    classifier = m_main_window->getClassifier();

    connect(button_aggregate, SIGNAL(clicked()), this, SLOT(aggregateResult()));
    connect(button_start_cancel, SIGNAL(clicked()), this, SLOT(startCancelProcess()));
    connect(button_pause_resume, SIGNAL(clicked()), this, SLOT(pauseResumeProcess()));

    connect(progressbar, SIGNAL(valueChanged()), this, SLOT(showResult()));
}

void ControlSection::startCancelProcess()
{
    if(button_start_cancel->text() == "Start") {
        button_start_cancel->setText("Cancel");
        button_pause_resume->setEnabled(true);

        // Start the Process
        classifier->run();

    } else {
        button_start_cancel->setText("Start");
        button_pause_resume->setEnabled(false);

        // Cancel the Process
        // LOSS OF THE FUNCTION!!
    }
}

void ControlSection::pauseResumeProcess()
{
    if (button_pause_resume->text() == "Pause") {
        button_pause_resume->setText("Resume");

        // Pause the Process
        classifier->pause();

    } else {
        button_pause_resume->setText("Pause");

        // Resume the Process
        classifier->resume();
    }
}

void ControlSection::aggregateResult()
{
    // aggregate the result
    Result res = datasaver->aggregate(assistant->getInputs());

    // convert std::string to QString
    QString str = QString::fromStdString(res.toString());

    // display the result with QLabel
    result->setText(str);
    result->setAlignment(Qt::AlignLeft);
    result->setWordWrap(true);
}

void ControlSection::showResult()
{
    if (progressbar->value() == 100) {
    	std::list<Image>::iterator iter = assistant->getInputs().begin();
    	QString str = "";

    	// combine results of all the input images
    	while (iter!= assistant->getInputs().end()) {
    		Result res = datasaver->getResult(*iter);
    		str +=  QString::fromStdString(res.toString()) + "\n\n\n";
    		iter++;
    	}

        // display the result with QLabel
        result->setText(str);
        result->setAlignment(Qt::AlignLeft);
        result->setWordWrap(true);
    }
}