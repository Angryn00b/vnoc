#include "UTProducer.h"
#include <iostream>

using namespace UTProduce::File;

void main()
{  
	UTProduce::XML::UTProducer utProducer;
	std::string strTempFileName;
	std::string strMsgDefFileName;

	std::cout<< "������UTģ���ļ�������(����0����Ĭ���ļ�): "<< std::endl;
	std::cin>>strTempFileName;
	if(strTempFileName == "0"){
		strTempFileName = "UTTemplate.msg";
	}

	std::cout<< "��������Ϣ�����ļ�������(����0����Ĭ���ļ�): "<< std::endl;
	std::cin>>strMsgDefFileName;
	if(strMsgDefFileName == "0"){
		strMsgDefFileName = "msgdef.xml";
	}
	
	if(utProducer.ProduceUTFile(strTempFileName, strMsgDefFileName)){
		std::cout<< "���ɳɹ�"<< std::endl;
	}else{
		std::cout<< "����ʧ��"<< std::endl;
	} 
	system("pause");
}															