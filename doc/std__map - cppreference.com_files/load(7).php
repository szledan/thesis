var placeholder_configs=[{pattern:'cpp/experimental/ranges',placeholder:'cpp/ranges-placeholder',matched:'cpp/experimental/ranges',unmatched:'cpp'},{pattern:'cpp/experimental/ranges',placeholder:'cpp/ranges-functional-placeholder',matched:'cpp/experimental/ranges/functional',unmatched:'cpp/functional/ranges'},{pattern:'cpp/experimental/ranges',placeholder:'cpp/ranges-algorithm-placeholder',matched:'cpp/experimental/ranges/algorithm',unmatched:'cpp/algorithm/ranges'},{pattern:'cpp/experimental/ranges',placeholder:'cpp/ranges-utility-placeholder',matched:'cpp/experimental/ranges/utility',unmatched:'cpp/utility/ranges'},{pattern:'cpp/experimental/ranges',placeholder:'cpp/ranges-iterator-placeholder',matched:'cpp/experimental/ranges/iterator',unmatched:'cpp/iterator/ranges'}];$.each(placeholder_configs,function(i,cf){if(mw.config.get('wgTitle').includes(cf.pattern)){$(function(){$('a[href*="'+cf.placeholder+'"]').each(function(){this.href=this.href.replace(cf.placeholder,cf.matched);});});
}else{$(function(){$('a[href*="'+cf.placeholder+'"]').each(function(){this.href=this.href.replace(cf.placeholder,cf.unmatched);});});}});;mw.loader.state({"site":"ready"});
/* cache key: mwiki1-mwiki_en_:resourceloader:filter:minify-js:7:fd43c0b39bbe211c3b756debf1a1396b */
/* Cached 20181023125223 */