//
// http://thecodeabode.blogspot.com
// @author: Ben Kitzelman
// @license:  FreeBSD: (http://opensource.org/licenses/BSD-2-Clause) Do whatever you like with it
// @updated: 03-03-2013
//
var getAcrobatInfo = function() {

  var getBrowserName = function() {
    return this.name = this.name || function() {
      var userAgent = navigator ? navigator.userAgent.toLowerCase() : "other";

      if(userAgent.indexOf("chrome") > -1)        return "chrome";
      else if(userAgent.indexOf("safari") > -1)   return "safari";
      else if(userAgent.indexOf("msie") > -1)     return "ie";
      else if(userAgent.indexOf("firefox") > -1)  return "firefox";
      return userAgent;
    }();
  };

  var getActiveXObject = function(name) {
    try { return new ActiveXObject(name); } catch(e) {}
  };

  var getNavigatorPlugin = function(name) {
    for(key in navigator.plugins) {
      var plugin = navigator.plugins[key];
      if(plugin.name == name) return plugin;
    }
  };

  var getPDFPlugin = function() {
    return this.plugin = this.plugin || function() {
      if(getBrowserName() == 'ie') {
        //
        // load the activeX control
        // AcroPDF.PDF is used by version 7 and later
        // PDF.PdfCtrl is used by version 6 and earlier
        return getActiveXObject('AcroPDF.PDF') || getActiveXObject('PDF.PdfCtrl');
      }
      else {
        return getNavigatorPlugin('Adobe Acrobat') || getNavigatorPlugin('Chrome PDF Viewer') || getNavigatorPlugin('WebKit built-in PDF');
      }
    }();
  };

  var isAcrobatInstalled = function() {
    return !!getPDFPlugin();
  };

  var getAcrobatVersion = function() {
    try {
      var plugin = getPDFPlugin();

      if(getBrowserName() == 'ie') {
        var versions = plugin.GetVersions().split(',');
        var latest   = versions[0].split('=');
        return parseFloat(latest[1]);
      }

      if(plugin.version) return parseInt(plugin.version);
      return plugin.name
    }
    catch(e) {
      return null;
    }
  }

  //
  // The returned object
  //
  return {
    browser:        getBrowserName(),
    acrobat:        isAcrobatInstalled() ? 'installed' : false,
    acrobatVersion: getAcrobatVersion()
  };
};
