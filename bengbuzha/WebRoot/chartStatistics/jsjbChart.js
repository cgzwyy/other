Ext.onReady(function() {

			Ext.QuickTips.init();
			Ext.getCmp('jsjbbtn').setText('<font color="red"><b>专业技术级别统计图</b></font>');
			Ext.getCmp('jsjbbtn').setHeight(25);
			var record = new Ext.data.Record.create([{
						name : 'jsjb'
					}, {
						name : 'data'
					}]);
			var store = new Ext.data.Store({

						proxy : new Ext.data.HttpProxy({
									url : __cxtPath
											+ '/orgMaint.do?method=getJsjbCount'
								}),
						reader : new Ext.data.JsonReader({
									root : 'rows'
								}, record),
						autoLoad : true,
						listeners:{
						
							load:function(){
								var temp='';
								for(var i=0;i<store.getCount();i++){
									temp= temp+'&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'+"<font color='blue'>"+store.getAt(i).get('jsjb')+'的人数:'+"</font>"+"<font color='red'>"+store.getAt(i).get('data')+"</font>";
								}
								Ext.getCmp('count').setTitle(temp);
							}
						}

					});
			var Chart = new Ext.Panel({
						title : '技术级别比例柱状图',
						width:860,
						height:400,
						items : {
							xtype : 'columnchart',
							store : store,
							url : __cxtPath + '/resources/charts.swf',
							xField : 'jsjb',
							yField : 'data',
							categoryField: 'jsjb',
							tipRenderer : function(chart, record, index, series){
						 return record.data.jsjb+'的人数：'+record.data.data;
						},
							listeners : {
								itemclick : function(o) {
									var rec = store.getAt(o.index);
									gridstore.setBaseParam('jsjb', rec.get('jsjb'));
									gridstore.reload();
								}
							}
							
//		  extraStyle:
//            {
//                legend:
//                {
//                    display: 'bottom',
//                    padding: 5,
//                    font:
//                    {
//                        family: 'Tahoma',
//                        size: 13
//                    }
//                }
//            }
						}
					});

					
var Chart1=	new Ext.Panel({
        title: '技术级别比例饼图',
       width:860,
	   height:400,
        items: {
            store: store,
            xtype: 'piechart',
            dataField: 'data',
            categoryField: 'jsjb',
            url : __cxtPath + '/resources/charts.swf',
            tipRenderer : function(chart, record, index, series){
						 return record.data.jsjb+'的人数：'+record.data.data;
						},
             listeners : {
								itemclick : function(o) {
									var rec = store.getAt(o.index);
									gridstore.setBaseParam('jsjb', rec.get('jsjb'));
									gridstore.reload();
								}
							},
			  extraStyle:
            {
                legend:
                {
                    display: 'bottom',
                    padding: 5,
                    font:
                    {
                        family: 'Tahoma',
                        size: 13
                    }
                }
            }
        }
       
    });
					
					
					var Botton = new Ext.Panel({
							width:500,
							border:false,
							layout:'column',
							buttons:[
								{
								xtype:'button',
								text:'柱状图',
								handler: function(){
									Chart1.hide();
									Chart.show();
								}
							},{
								xtype:'button',
								text:'饼图',
								handler: function(){
									Chart1.show();
									Chart.hide();
								}
							}
							]
							
					});
			var gridrecord = Ext.data.Record.create([{
						name : 'name'
					}, {
						name : 'jsjb'
					}]);
			var gridstore = new Ext.data.Store({
						proxy : new Ext.data.HttpProxy({
									url : __cxtPath
											+ '/orgMaint.do?method=getJsjbList'
								}),
						baseParams : {
							start : 0,
							limit : 20,
							jsjb : '高级'
						},
						reader : new Ext.data.JsonReader({
									root : 'rows',
									totalProperty : 'totalCount'
								}, gridrecord),
						autoLoad : true
					});
			var cm = new Ext.grid.ColumnModel([new Ext.grid.RowNumberer({
								header : '序号',
								width : 50
							}), {
						header : '姓名',
						dataIndex : 'name'
					}, {
						header : '技术职称',
						dataIndex : 'jsjb',
						sortable : true
					}]);
			Grid = new Ext.grid.GridPanel({
						title : '技术级别比例统计表',
						region:'east',
						border : false,
						width : 300,
						loadMask : true,
						collapsible : true,
						autoScroll : true,
						collapseMode : 'mini',
						loadMask : {
							msg : '正在加载数据，请稍侯……'
						},
						stripeRows : true,
						store : gridstore,
						cm : cm,
						
						bbar : new Ext.PagingToolbar({
									pageSize : 20,
									store : gridstore,
									displayInfo : true,
									displayMsg : '当前显示 {0} - {1} 条记录 /共 {2} 条记录',
									emptyMsg : "无显示数据",
									plugins : [new Ext.ux.PagelimitCombo()]
								})

					});
					var menu = xmis.chartStatistics.menu;
					var count = new Ext.Panel({
						width:860,
						height:20,
						border:false,
						title : ' ',
						id:'count'
					});
					Chart1.hide();
		 	new Ext.Viewport({
						border : false,
						layout : 'border',
						items : [{
							region:'center',
               				 margins:'35 5 5 0',
               				 border : false,
               				 layout:'column',
              				  items:[Chart,Chart1,Botton,count]
						},Grid,menu]
					});
		});