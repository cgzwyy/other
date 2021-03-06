select * into xmis.con_收款条件表_history from xmis.con_收款条件表

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TRIGGER xmis.con_收款条件表_trigger 
   ON xmis.con_收款条件表
   AFTER INSERT,UPDATE
AS 
BEGIN
	SET NOCOUNT ON;
	DECLARE @cID INT,@pID INT
	
	IF EXISTS (SELECT 1 FROM INSERTED ) AND NOT EXISTS (SELECT 1 FROM DELETED)
		begin
			SELECT @cID = INSERTED.合同ID,@pID = INSERTED.收款条件ID FROM INSERTED
			insert into xmis.con_收款条件表_history select * from xmis.con_收款条件表 WHERE 合同ID = @cID and 收款条件ID = @pID;
		end
	ELSE IF EXISTS (SELECT 1 FROM INSERTED ) AND EXISTS (SELECT 1 FROM DELETED)
		begin
			SELECT @cID = DELETED.合同ID,@pID = DELETED.收款条件ID FROM DELETED
			insert into xmis.con_收款条件表_history select * from xmis.con_收款条件表 WHERE 合同ID = @cID and 收款条件ID = @pID;
		end
END
GO