
  alter table [xmis].[xmis].[con_合同] add 有效期限 float,有效期计量单位 int,有效期起 datetime,有效期止 datetime
  alter table [xmis].[xmis].[con_合同_history] add 有效期限 float,有效期计量单位 int,有效期起 datetime,有效期止 datetime
  
  
  insert into [xmis].[xmis].[sys_附件主体类型] values(6,'项目附件','xmis.prj_项目','',null,null)
  
  alter table [xmis].[xmis].[wf_待办] add 描述 nvarchar(2000),发送人 int,发送时间 datetime
  alter table [xmis].[xmis].[con_收款条件表] add 收款节点名称 nvarchar(20)
  
  create table xmis.prj_项目进度计划(
	ID nvarchar(50),
	项目ID nvarchar(32) null,
	项目状态ID smallint not null,
	预计开始日期 datetime not null,
	实际开始日期 datetime,
	最后修改日期 datetime,
	最后修改人ID int
  )
  