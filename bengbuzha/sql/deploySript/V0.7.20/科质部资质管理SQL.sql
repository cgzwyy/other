
  
  insert into [xmis].[xmis].[sec_业务子模块表]
  values(41,'计算机信息系统集成项目汇总表','contract/contractAmtSplitList.jsp','计算机信息系统集成项目汇总表',null,null,null,null,null,null,null,null,null)
  
  insert into [xmis].[xmis].[sec_业务功能表]
  values(31,'计算机信息系统集成项目汇总表',null,'计算机信息系统集成项目汇总表',null,38,null,null,null,null,null,null,null)
  
  update [xmis].[xmis].[sec_业务模块对应表] set 业务子模块排列顺序 = 2 where 业务模块ID = 5 and 业务子模块ID = 7
  
  insert into [xmis].[xmis].[sec_业务模块对应表] 
  values(5,41,1,GETDATE(),-1)
  
  insert into [xmis].[xmis].[sec_角色用户操作权限定义表]
  values(105,7,5,41,31,5,1,GETDATE(),-1)