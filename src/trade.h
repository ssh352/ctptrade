#ifndef __TRADE_H
#define __TRADE_H

#include "common.h"

typedef struct TdStruct
{
	 char FRONT_ADDR[100];
	 TThostFtdcBrokerIDType BROKER_ID;
	 TThostFtdcInvestorIDType INVESTOR_ID;
	 TThostFtdcPasswordKeyType PASSWORD;
};
TdStruct jy;

//合约结构
typedef struct HyStruct
{
	  int hycs;
	  double hyds;
};

class CTradeHandler : public CThostFtdcTraderSpi
{
	public:
		 HyStruct hy(QString);
		 void Init();
		 CThostFtdcTraderApi* pUserApi;
		 CTradeHandler();
		 ~CTradeHandler();

		 ///报单录入请求
		 void ReqOrderInsert(QString dm,QString lx,int lots,double price);
		 ///报单操作请求
		 void ReqOrderAction(QString brokerid,QString wth,QString jys);
		 ///报单操作请求
		 //void ReqOrderAction(CThostFtdcOrderField *pOrder);

		 ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
		 virtual void OnFrontConnected();

		 ///登录请求响应
		 virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		 ///投资者结算结果确认响应
		 virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		 ///请求查询合约响应---合约查询
		 virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		 ///请求查询资金账户响应  --资金查询
		 virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		 ///请求查询投资者持仓响应--  持仓查询
		 virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		 ///报单录入请求响应
		 virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		 ///报单操作请求响应
		 virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		 ///错误应答
		 virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		 ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
		 virtual void OnFrontDisconnected(int nReason);
 
		 ///心跳超时警告。当长时间未收到报文时，该方法被调用。
		 virtual void OnHeartBeatWarning(int nTimeLapse);

		 ///报单通知--------------/委托回报
		 virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);

		 ///成交通知--------------/成交回报
	  	 virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

	private:
		 ///用户登录请求
		 void ReqUserLogin();
		 ///投资者结算结果确认
		 void ReqSettlementInfoConfirm();
		 ///请求查询合约
		 void ReqQryInstrument();
		 ///请求查询资金账户
		 void ReqQryTradingAccount();
		 ///请求查询投资者持仓
		 void ReqQryInvestorPosition();


		 // 是否收到成功的响应
		 bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);
		 // 是否我的报单回报
		 bool IsMyOrder(CThostFtdcOrderField *pOrder);
		 // 是否正在交易的报单
		 bool IsTradingOrder(CThostFtdcOrderField *pOrder);
};

#endif // CTradeHandler_H
