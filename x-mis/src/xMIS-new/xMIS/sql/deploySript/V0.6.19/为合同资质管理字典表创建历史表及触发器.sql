select * into xmis.sys_合同资质管理字典表_history from xmis.sys_合同资质管理字典表

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TRIGGER xmis.sys_合同资质管理字典表_trigger 
   ON xmis.sys_合同资质管理字典表
   AFTER INSERT,UPDATE
AS 
BEGIN
	SET NOCOUNT ON;
	DECLARE @ID INT
	
	IF EXISTS (SELECT 1 FROM INSERTED ) AND NOT EXISTS (SELECT 1 FROM DELETED)
		begin
			SELECT @ID = INSERTED.ID FROM INSERTED
			insert into xmis.sys_合同资质管理字典表_history select * from xmis.sys_合同资质管理字典表 WHERE ID = @ID;
		end
	ELSE IF EXISTS (SELECT 1 FROM INSERTED ) AND EXISTS (SELECT 1 FROM DELETED)
		begin
			SELECT @ID = DELETED.ID FROM DELETED
			insert into xmis.sys_合同资质管理字典表_history select * from xmis.sys_合同资质管理字典表 WHERE ID = @ID;
		end
END
GO