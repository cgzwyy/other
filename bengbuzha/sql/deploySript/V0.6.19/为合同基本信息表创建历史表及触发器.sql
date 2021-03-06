select * into xmis.con_合同基本信息_history from xmis.con_合同基本信息

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TRIGGER xmis.con_合同基本信息_trigger 
   ON xmis.con_合同基本信息
   AFTER INSERT,UPDATE
AS 
BEGIN
	SET NOCOUNT ON;
	DECLARE @ID INT
	
	IF EXISTS (SELECT 1 FROM INSERTED ) AND NOT EXISTS (SELECT 1 FROM DELETED)
		begin
			SELECT @ID = INSERTED.合同ID FROM INSERTED
			insert into xmis.con_合同基本信息_history select * from xmis.con_合同基本信息 WHERE 合同ID = @ID;
		end
	ELSE IF EXISTS (SELECT 1 FROM INSERTED ) AND EXISTS (SELECT 1 FROM DELETED)
		begin
			SELECT @ID = DELETED.合同ID FROM DELETED
			insert into xmis.con_合同基本信息_history select * from xmis.con_合同基本信息 WHERE 合同ID = @ID;
		end
END
GO