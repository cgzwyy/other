
/*
===================================================================
Copyright DHTMLX LTD. http://www.dhtmlx.com
This code is obfuscated and not allowed for any purposes except 
using on sites which belongs to DHTMLX LTD.

Please contact sales@dhtmlx.com to obtain necessary 
license for usage of dhtmlx components.
===================================================================
*/
dhtmlx = function (obj) {
	for (var a in obj) {
		dhtmlx[a] = obj[a];
	}
	return dhtmlx;
};
dhtmlx.extend_api = function (name, map, ext) {
	var t = window[name];
	if (!t) {
		return;
	}
	window[name] = function (obj) {
		if (obj && typeof obj == "object" && !obj.tagName) {
			var that = t.apply(this, (map.ahY ? map.ahY(obj) : arguments));
			for (var a in dhtmlx) {
				if (map[a]) {
					this[map[a]](dhtmlx[a]);
				}
			}
			for (var a in obj) {
				if (map[a]) {
					this[map[a]](obj[a]);
				} else {
					if (a.indexOf("on") == 0) {
						this.attachEvent(a, obj[a]);
					}
				}
			}
		} else {
			var that = t.apply(this, arguments);
		}
		if (map._patch) {
			map._patch(this);
		}
		return that || this;
	};
	window[name].prototype = t.prototype;
	if (ext) {
		oT(window[name].prototype, ext);
	}
};
dhtmlxAjax = {get:function (url, Eq) {
	var t = new ag(true);
	t.async = (arguments.length < 3);
	t.bs = Eq;
	t.loadXML(url);
	return t;
}, post:function (url, post, Eq) {
	var t = new ag(true);
	t.async = (arguments.length < 4);
	t.bs = Eq;
	t.loadXML(url, true, post);
	return t;
}, getSync:function (url) {
	return this.get(url, null, true);
}, postSync:function (url, post) {
	return this.post(url, post, null, true);
}};
function ag(dR, Ll, async, hN) {
	this.ai = "";
	if (typeof (async) != "undefined") {
		this.async = async;
	} else {
		this.async = true;
	}
	this.UR = dR || null;
	this.cT = Ll || null;
	this.bs = null;
	this.hN = hN || false;
	return this;
}
ag.prototype.cz = function (Ll) {
	var once = true;
	this.jC = function () {
		if ((Ll) && (Ll.UR != null)) {
			if ((!Ll.ai.readyState) || (Ll.ai.readyState == 4)) {
				if (!once) {
					return;
				}
				once = false;
				if (typeof Ll.UR == "function") {
					Ll.UR(Ll.cT, null, null, null, Ll);
				}
				if (Ll.bs) {
					Ll.bs.call(this, Ll);
					Ll.bs = null;
				}
			}
		}
	};
	return this.jC;
};
ag.prototype.cR = function (tagName, Db) {
	if (this.ai.responseXML) {
		var AT = this.ai.responseXML.getElementsByTagName(tagName);
		if (AT.length == 0 && tagName.indexOf(":") != -1) {
			var AT = this.ai.responseXML.getElementsByTagName((tagName.split(":"))[1]);
		}
		var z = AT[0];
	} else {
		var z = this.ai.documentElement;
	}
	if (z) {
		this.jV = false;
		return z;
	}
	if ((_isIE) && (!this.jV)) {
		var RA = this.ai.responseText;
		var Db = this.ai;
		this.jV = true;
		this.ai = new ActiveXObject("Microsoft.XMLDOM");
		this.ai.async = false;
		this.ai["loadXM" + "L"](RA);
		return this.cR(tagName, Db);
	}
	ey.gn("LoadXML", "Incorrect XML", [(Db || this.ai), this.cT]);
	return document.createElement("DIV");
};
ag.prototype.loadXMLString = function (RA) {
	try {
		var qi = new DOMParser();
		this.ai = qi.parseFromString(RA, "text/xml");
	}
	catch (e) {
		this.ai = new ActiveXObject("Microsoft.XMLDOM");
		this.ai.async = this.async;
		this.ai["loadXM" + "L"](RA);
	}
	this.UR(this.cT, null, null, null, this);
	if (this.bs) {
		this.bs();
		this.bs = null;
	}
};
ag.prototype.loadXML = function (bU, fk, iV, rpc) {
	if (this.hN) {
		bU += ((bU.indexOf("?") != -1) ? "&" : "?") + "a_dhx_rSeed=" + (new Date()).valueOf();
	}
	this.bU = bU;
	if ((!_isIE) && (window.XMLHttpRequest)) {
		this.ai = new XMLHttpRequest();
	} else {
		if (document.implementation && document.implementation.createDocument) {
			this.ai = document.implementation.createDocument("", "", null);
			this.ai.onload = new this.cz(this);
			this.ai.load(bU);
			return;
		} else {
			this.ai = new ActiveXObject("Microsoft.XMLHTTP");
		}
	}
	if (this.async) {
		this.ai.onreadystatechange = new this.cz(this);
	}
	this.ai.open(fk ? "POST" : "GET", bU, this.async);
	if (rpc) {
		this.ai.setRequestHeader("User-Agent", "dhtmlxRPC v0.1 (" + navigator.userAgent + ")");
		this.ai.setRequestHeader("Content-type", "text/xml");
	} else {
		if (fk) {
			this.ai.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
		}
	}
	this.ai.setRequestHeader("X-Requested-With", "XMLHttpRequest");
	this.ai.send(null || iV);
	if (!this.async) {
		(new this.cz(this))();
	}
};
ag.prototype.fA = function () {
	this.UR = null;
	this.cT = null;
	this.ai = null;
	return null;
};
ag.prototype.xmlNodeToJSON = function (node) {
	var t = {};
	for (var i = 0; i < node.attributes.length; i++) {
		t[node.attributes[i].name] = node.attributes[i].value;
	}
	t["_tagvalue"] = node.firstChild ? node.firstChild.nodeValue : "";
	for (var i = 0; i < node.childNodes.length; i++) {
		var name = node.childNodes[i].tagName;
		if (name) {
			if (!t[name]) {
				t[name] = [];
			}
			t[name].push(this.xmlNodeToJSON(node.childNodes[i]));
		}
	}
	return t;
};
function jP(dR, Ll) {
	this.handler = function (e) {
		if (!e) {
			e = window.event;
		}
		dR(e, Ll);
		return true;
	};
	return this.handler;
}
function ej(aI) {
	return getOffset(aI).left;
}
function dg(aI) {
	return getOffset(aI).top;
}
function getOffsetSum(elem) {
	var top = 0, left = 0;
	while (elem) {
		top = top + parseInt(elem.offsetTop);
		left = left + parseInt(elem.offsetLeft);
		elem = elem.offsetParent;
	}
	return {top:top, left:left};
}
function getOffsetRect(elem) {
	var box = elem.getBoundingClientRect();
	var body = document.body;
	var docElem = document.documentElement;
	var scrollTop = window.pageYOffset || docElem.scrollTop || body.scrollTop;
	var scrollLeft = window.pageXOffset || docElem.scrollLeft || body.scrollLeft;
	var clientTop = docElem.clientTop || body.clientTop || 0;
	var clientLeft = docElem.clientLeft || body.clientLeft || 0;
	var top = box.top + scrollTop - clientTop;
	var left = box.left + scrollLeft - clientLeft;
	return {top:Math.round(top), left:Math.round(left)};
}
function getOffset(elem) {
	if (elem.getBoundingClientRect && !_isChrome) {
		return getOffsetRect(elem);
	} else {
		return getOffsetSum(elem);
	}
}
function K(cy) {
	if (typeof (cy) == "string") {
		cy = cy.toLowerCase();
	}
	switch (cy) {
	  case "1":
	  case "true":
	  case "yes":
	  case "y":
	  case 1:
	  case true:
		return true;
		break;
	  default:
		return false;
	}
}
function jv(str) {
	if (str.indexOf("?") != -1) {
		return "&";
	} else {
		return "?";
	}
}
function J() {
	if (window.F) {
		return window.F;
	}
	this.aG = 0;
	this.al = 0;
	this.bh = 0;
	this.aM = 0;
	this.dG = null;
	this.dH = null;
	this.PF = 0;
	window.F = this;
	return this;
}
J.prototype.fG = function (ao) {
	ao.onmousedown = null;
	ao.eO = null;
	ao.aK = null;
};
J.prototype.dS = function (ao, Ll) {
	ao.onmousedown = this.bR;
	ao.eO = Ll;
	this.eH(ao, Ll);
};
J.prototype.eH = function (ao, Ll) {
	ao.aK = Ll;
};
J.prototype.bR = function (e) {
	if ((e || event) && (e || event).button == 2) {
		return;
	}
	if (window.F.PF) {
		window.F.PF = 0;
		document.body.onmouseup = window.F.dG;
		document.body.onmousemove = window.F.dH;
		return false;
	}
	window.F.PF = 1;
	window.F.dG = document.body.onmouseup;
	window.F.dH = document.body.onmousemove;
	window.F.bh = this;
	window.F.aM = this.eO;
	document.body.onmouseup = window.F.bR;
	document.body.onmousemove = window.F.kU;
	if ((e) && (e.preventDefault)) {
		e.preventDefault();
		return false;
	}
	return false;
};
J.prototype.kU = function (e) {
	if (!e) {
		e = window.event;
	}
	M = window.F;
	if ((e.button == 0) && (_isIE)) {
		return M.dc();
	}
	if (!M.al && M.PF) {
		M.al = M.aM.gL(M.bh, e);
		if (!M.al) {
			return M.dc();
		}
		M.al.onselectstart = function () {
			return false;
		};
		M.bN = M.al;
		document.body.appendChild(M.al);
		document.body.onmouseup = M.dc;
		M.PF = 0;
		M.al.aR = window;
		M.bm();
	}
	if (M.al.parentNode != window.document.body) {
		var qp = M.bN;
		if (M.bN.old) {
			qp = M.bN.old;
		}
		qp.parentNode.removeChild(qp);
		var nD = M.al.aR;
		if (_isIE) {
			var div = document.createElement("Div");
			div.innerHTML = M.al.outerHTML;
			M.al = div.childNodes[0];
		} else {
			M.al = M.al.cloneNode(true);
		}
		M.al.aR = window;
		M.bN.old = M.al;
		document.body.appendChild(M.al);
		nD.F.al = M.al;
	}
	M.al.style.left = e.clientX + 15 + (M.fx ? M.fx * (-1) : 0) + (document.body.scrollLeft || document.documentElement.scrollLeft) + "px";
	M.al.style.top = e.clientY + 3 + (M.fy ? M.fy * (-1) : 0) + (document.body.scrollTop || document.documentElement.scrollTop) + "px";
	if (!e.srcElement) {
		var z = e.target;
	} else {
		z = e.srcElement;
	}
	M.eq(z, e);
};
J.prototype.bS = function (n) {
	if (window.name) {
		var el = parent.frames[window.name].frameElement.offsetParent;
		var fx = 0;
		var fy = 0;
		while (el) {
			fx += el.offsetLeft;
			fy += el.offsetTop;
			el = el.offsetParent;
		}
		if ((parent.F)) {
			var ls = parent.F.bS(1);
			fx += ls.split("_")[0] * 1;
			fy += ls.split("_")[1] * 1;
		}
		if (n) {
			return fx + "_" + fy;
		} else {
			this.fx = fx;
		}
		this.fy = fy;
	}
	return "0_0";
};
J.prototype.eq = function (aI, e) {
	if ((aI) && (aI.aK)) {
		if (this.aG) {
			this.aG.aK.iX(this.aG);
		}
		this.aG = aI;
		this.aG = this.aG.aK.tY(this.aG, this.bh, e.clientX, e.clientY, e);
		this.wS = (_isIE ? e.srcElement : e.target);
	} else {
		if ((aI) && (aI.tagName != "BODY")) {
			this.eq(aI.parentNode, e);
		} else {
			if (this.aG) {
				this.aG.aK.iX(this.aG, e.clientX, e.clientY, e);
			}
			this.aG = 0;
			if (this.hq) {
				this.hq();
			}
		}
	}
};
J.prototype.dc = function (e, mode) {
	M = window.F;
	if (!mode) {
		M.PE();
		var AT = M.aG;
		M.aG = null;
		if (AT) {
			AT.aK.BK(M.bh, M.aM, AT, (_isIE ? event.srcElement : e.target));
		}
	}
	M.aG = null;
	if ((M.al) && (M.al.parentNode == document.body)) {
		M.al.parentNode.removeChild(M.al);
	}
	M.al = 0;
	M.bN = 0;
	M.fx = 0;
	M.fy = 0;
	M.bh = 0;
	M.aM = 0;
	document.body.onmouseup = M.dG;
	document.body.onmousemove = M.dH;
	M.dG = null;
	M.dH = null;
	M.PF = 0;
};
J.prototype.PE = function (win) {
	if (win) {
		window.F.dc(1, 1);
	}
	for (var i = 0; i < window.frames.length; i++) {
		try {
			if ((window.frames[i] != win) && (window.frames[i].F)) {
				window.frames[i].F.PE(window);
			}
		}
		catch (e) {
		}
	}
	try {
		if ((parent.F) && (parent != window) && (parent != win)) {
			parent.F.PE(window);
		}
	}
	catch (e) {
	}
};
J.prototype.bm = function (win, mode) {
	if (win) {
		window.F.bR();
		window.F.bh = win.F.bh;
		window.F.aM = win.F.aM;
		window.F.al = win.F.al;
		window.F.bN = win.F.al;
		window.document.body.onmouseup = window.F.dc;
		window.PF = 0;
		if (((!_isIE) && (mode)) && ((!aq) || (qG < 1.8))) {
			window.F.bS();
		}
	}
	try {
		if ((parent.F) && (parent != window) && (parent != win)) {
			parent.F.bm(window);
		}
	}
	catch (e) {
	}
	for (var i = 0; i < window.frames.length; i++) {
		try {
			if ((window.frames[i] != win) && (window.frames[i].F)) {
				window.frames[i].F.bm(window, ((!win || mode) ? 1 : 0));
			}
		}
		catch (e) {
		}
	}
};
var aq = false;
var _isIE = false;
var cU = false;
var cn = false;
var gP = false;
var _isChrome = false;
if (navigator.userAgent.indexOf("Macintosh") != -1) {
	gP = true;
}
if (navigator.userAgent.toLowerCase().indexOf("chrome") > -1) {
	_isChrome = true;
}
if ((navigator.userAgent.indexOf("Safari") != -1) || (navigator.userAgent.indexOf("Konqueror") != -1)) {
	var _KHTMLrv = parseFloat(navigator.userAgent.substr(navigator.userAgent.indexOf("Safari") + 7, 5));
	if (_KHTMLrv > 525) {
		aq = true;
		var qG = 1.9;
	} else {
		cn = true;
	}
} else {
	if (navigator.userAgent.indexOf("Opera") != -1) {
		cU = true;
		pe = parseFloat(navigator.userAgent.substr(navigator.userAgent.indexOf("Opera") + 6, 3));
	} else {
		if (navigator.appName.indexOf("Microsoft") != -1) {
			_isIE = true;
			if (navigator.appVersion.indexOf("MSIE 8.0") != -1 && document.compatMode != "BackCompat") {
				_isIE = 8;
			}
		} else {
			aq = true;
			var qG = parseFloat(navigator.userAgent.split("rv:")[1]);
		}
	}
}
ag.prototype.et = function (df, bc, namespace, result_type) {
	if (cn || (!_isIE && !window.XPathResult)) {
		return this.hi(df, bc);
	}
	if (_isIE) {
		if (!bc) {
			if (!this.ai.nodeName) {
				bc = this.ai.responseXML;
			} else {
				bc = this.ai;
			}
		}
		if (!bc) {
			ey.gn("LoadXML", "Incorrect XML", [(bc || this.ai), this.cT]);
		}
		if (namespace != null) {
			bc.setProperty("SelectionNamespaces", "xmlns:xsl='" + namespace + "'");
		}
		if (result_type == "single") {
			return bc.selectSingleNode(df);
		} else {
			return bc.selectNodes(df) || new Array(0);
		}
	} else {
		var gb = bc;
		if (!bc) {
			if (!this.ai.nodeName) {
				bc = this.ai.responseXML;
			} else {
				bc = this.ai;
			}
		}
		if (!bc) {
			ey.gn("LoadXML", "Incorrect XML", [(bc || this.ai), this.cT]);
		}
		if (bc.nodeName.indexOf("document") != -1) {
			gb = bc;
		} else {
			gb = bc;
			bc = bc.ownerDocument;
		}
		var retType = XPathResult.ANY_TYPE;
		if (result_type == "single") {
			retType = XPathResult.FIRST_ORDERED_NODE_TYPE;
		}
		var P = new Array();
		var col = bc.evaluate(df, gb, function (apG) {
			return namespace;
		}, retType, null);
		if (retType == XPathResult.FIRST_ORDERED_NODE_TYPE) {
			return col.singleNodeValue;
		}
		var dv = col.iterateNext();
		while (dv) {
			P[P.length] = dv;
			dv = col.iterateNext();
		}
		return P;
	}
};
function de(type, name, params) {
	if (!this.cW) {
		this.cW = new Array();
	}
	return this;
}
de.prototype.mP = function (type, jT) {
	this.cW[type] = jT;
};
de.prototype.gn = function (type, name, params) {
	if (this.cW[type]) {
		return this.cW[type](type, name, params);
	}
	if (this.cW["ALL"]) {
		return this.cW["ALL"](type, name, params);
	}
	alert("Error type: " + arguments[0] + "\nDescription: " + arguments[1]);
	return null;
};
window.ey = new de();
ag.prototype.hi = function (df, bc) {
	var z = df.replace(/[\/]+/gi, "/").split("/");
	var obj = null;
	var i = 1;
	if (!z.length) {
		return [];
	}
	if (z[0] == ".") {
		obj = [bc];
	} else {
		if (z[0] == "") {
			obj = (this.ai.responseXML || this.ai).getElementsByTagName(z[i].replace(/\[[^\]]*\]/g, ""));
			i++;
		} else {
			return [];
		}
	}
	for (i; i < z.length; i++) {
		obj = this.eo(obj, z[i]);
	}
	if (z[i - 1].indexOf("[") != -1) {
		obj = this.hj(obj, z[i - 1]);
	}
	return obj;
};
ag.prototype.hj = function (a, b) {
	var c = new Array();
	var b = b.replace(/[^\[]*\[\@/g, "").replace(/[\[\]\@]*/g, "");
	for (var i = 0; i < a.length; i++) {
		if (a[i].getAttribute(b)) {
			c[c.length] = a[i];
		}
	}
	return c;
};
ag.prototype.eo = function (a, b) {
	var c = new Array();
	if (cn) {
		b = b.toUpperCase();
	}
	for (var i = 0; i < a.length; i++) {
		for (var j = 0; j < a[i].childNodes.length; j++) {
			if (cn) {
				if (a[i].childNodes[j].tagName && a[i].childNodes[j].tagName.toUpperCase() == b) {
					c[c.length] = a[i].childNodes[j];
				}
			} else {
				if (a[i].childNodes[j].tagName == b) {
					c[c.length] = a[i].childNodes[j];
				}
			}
		}
	}
	return c;
};
function oT(a, b) {
	for (var c in b) {
		if (typeof (b[c]) == "function") {
			a[c] = b[c];
		}
	}
	return a;
}
function dE(el, event, handler) {
	if (el.addEventListener) {
		el.addEventListener(event, handler, false);
	} else {
		if (el.attachEvent) {
			el.attachEvent("on" + event, handler);
		}
	}
}
ag.prototype.xslDoc = null;
ag.prototype.setXSLParamValue = function (paramName, paramValue, xslDoc) {
	if (!xslDoc) {
		xslDoc = this.xslDoc;
	}
	if (xslDoc.responseXML) {
		xslDoc = xslDoc.responseXML;
	}
	var item = this.et("/xsl:stylesheet/xsl:variable[@name='" + paramName + "']", xslDoc, "http://www.w3.org/1999/XSL/Transform", "single");
	if (item != null) {
		item.firstChild.nodeValue = paramValue;
	}
};
ag.prototype.doXSLTransToObject = function (xslDoc, ai) {
	if (!xslDoc) {
		xslDoc = this.xslDoc;
	}
	if (xslDoc.responseXML) {
		xslDoc = xslDoc.responseXML;
	}
	if (!ai) {
		ai = this.ai;
	}
	if (ai.responseXML) {
		ai = ai.responseXML;
	}
	if (!_isIE) {
		if (!this.XSLProcessor) {
			this.XSLProcessor = new XSLTProcessor();
			this.XSLProcessor.importStylesheet(xslDoc);
		}
		var result = this.XSLProcessor.transformToDocument(ai);
	} else {
		var result = new ActiveXObject("Msxml2.DOMDocument.3.0");
		try {
			ai.transformNodeToObject(xslDoc, result);
		}
		catch (e) {
			result = ai.transformNode(xslDoc);
		}
	}
	return result;
};
ag.prototype.doXSLTransToString = function (xslDoc, ai) {
	var res = this.doXSLTransToObject(xslDoc, ai);
	if (typeof (res) == "string") {
		return res;
	}
	return this.doSerialization(res);
};
ag.prototype.doSerialization = function (ai) {
	if (!ai) {
		ai = this.ai;
	}
	if (ai.responseXML) {
		ai = ai.responseXML;
	}
	if (!_isIE) {
		var kE = new XMLSerializer();
		return kE.serializeToString(ai);
	} else {
		return ai.xml;
	}
};
dhtmlxEventable = function (obj) {
	obj.bJ = "";
	obj.attachEvent = function (name, hk, callObj) {
		name = "ev_" + name.toLowerCase();
		if (!this[name]) {
			this[name] = new this.eventCatcher(callObj || this);
		}
		return (name + ":" + this[name].oe(hk));
	};
	obj.callEvent = function (name, afo) {
		name = "ev_" + name.toLowerCase();
		if (this[name]) {
			return this[name].apply(this, afo);
		}
		return true;
	};
	obj.mR = function (name) {
		return (!!this["ev_" + name.toLowerCase()]);
	};
	obj.eventCatcher = function (obj) {
		var gu = [];
		var z = function () {
			var res = true;
			for (var i = 0; i < gu.length; i++) {
				if (gu[i] != null) {
					var zr = gu[i].apply(obj, arguments);
					res = res && zr;
				}
			}
			return res;
		};
		z.oe = function (ev) {
			if (typeof (ev) != "function") {
				ev = eval(ev);
			}
			if (ev) {
				return gu.push(ev) - 1;
			}
			return false;
		};
		z.uI = function (id) {
			gu[id] = null;
		};
		return z;
	};
	obj.detachEvent = function (id) {
		if (id != false) {
			var list = id.split(":");
			this[list[0]].uI(list[1]);
		}
	};
};
