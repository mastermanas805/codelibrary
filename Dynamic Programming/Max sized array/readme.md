
```html
<script src="https://polyfill.io/v3/polyfill.min.js?features=es6"></script>
<script id="MathJax-script" async src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-mml-chtml.js"></script>

<div class="semi-bold margin-bottom-20">Max sized array</div><div class="algorithm-problem complete-problem-statement dark"><p>You are given <em>3D</em>&nbsp;array <em>A</em> of dimensions&nbsp;<em>N*N*N</em>,&nbsp;where any element <em>A[ i ][ j ][ k ]</em> of&nbsp;<em>A </em>equals&nbsp;<em>i*k*( i + j + k )&nbsp;</em><span class="mathjax-latex"><span class="MathJax_Preview" style="color: inherit; --darkreader-inline-color: inherit;" data-darkreader-inline-color=""></span><span style="font-size: 100%; display: inline-block; position: relative;" class="MathJax_SVG" id="MathJax-Element-14-Frame" tabindex="0" data-mathml="<math xmlns=&quot;http://www.w3.org/1998/Math/MathML&quot;><mo stretchy=&quot;false&quot;>(</mo><mn>1</mn><mo>&amp;#x2264;</mo><mi>i</mi><mo>,</mo><mi>j</mi><mo>,</mo><mi>k</mi><mo>&amp;#x2264;</mo><mi>N</mi><mo stretchy=&quot;false&quot;>)</mo></math>" role="presentation"><svg xmlns:xlink="http://www.w3.org/1999/xlink" width="16.272ex" height="3.812ex" style="vertical-align: -1.272ex;" viewBox="0 -1093.5 7005.9 1641.3" role="img" focusable="false" aria-hidden="true"><defs><path stroke-width="1" id="E14-MJMAIN-28" d="M94 250Q94 319 104 381T127 488T164 576T202 643T244 695T277 729T302 750H315H319Q333 750 333 741Q333 738 316 720T275 667T226 581T184 443T167 250T184 58T225 -81T274 -167T316 -220T333 -241Q333 -250 318 -250H315H302L274 -226Q180 -141 137 -14T94 250Z"></path><path stroke-width="1" id="E14-MJMAIN-31" d="M213 578L200 573Q186 568 160 563T102 556H83V602H102Q149 604 189 617T245 641T273 663Q275 666 285 666Q294 666 302 660V361L303 61Q310 54 315 52T339 48T401 46H427V0H416Q395 3 257 3Q121 3 100 0H88V46H114Q136 46 152 46T177 47T193 50T201 52T207 57T213 61V578Z"></path><path stroke-width="1" id="E14-MJMAIN-2264" d="M674 636Q682 636 688 630T694 615T687 601Q686 600 417 472L151 346L399 228Q687 92 691 87Q694 81 694 76Q694 58 676 56H670L382 192Q92 329 90 331Q83 336 83 348Q84 359 96 365Q104 369 382 500T665 634Q669 636 674 636ZM84 -118Q84 -108 99 -98H678Q694 -104 694 -118Q694 -130 679 -138H98Q84 -131 84 -118Z"></path><path stroke-width="1" id="E14-MJMATHI-69" d="M184 600Q184 624 203 642T247 661Q265 661 277 649T290 619Q290 596 270 577T226 557Q211 557 198 567T184 600ZM21 287Q21 295 30 318T54 369T98 420T158 442Q197 442 223 419T250 357Q250 340 236 301T196 196T154 83Q149 61 149 51Q149 26 166 26Q175 26 185 29T208 43T235 78T260 137Q263 149 265 151T282 153Q302 153 302 143Q302 135 293 112T268 61T223 11T161 -11Q129 -11 102 10T74 74Q74 91 79 106T122 220Q160 321 166 341T173 380Q173 404 156 404H154Q124 404 99 371T61 287Q60 286 59 284T58 281T56 279T53 278T49 278T41 278H27Q21 284 21 287Z"></path><path stroke-width="1" id="E14-MJMAIN-2C" d="M78 35T78 60T94 103T137 121Q165 121 187 96T210 8Q210 -27 201 -60T180 -117T154 -158T130 -185T117 -194Q113 -194 104 -185T95 -172Q95 -168 106 -156T131 -126T157 -76T173 -3V9L172 8Q170 7 167 6T161 3T152 1T140 0Q113 0 96 17Z"></path><path stroke-width="1" id="E14-MJMATHI-6A" d="M297 596Q297 627 318 644T361 661Q378 661 389 651T403 623Q403 595 384 576T340 557Q322 557 310 567T297 596ZM288 376Q288 405 262 405Q240 405 220 393T185 362T161 325T144 293L137 279Q135 278 121 278H107Q101 284 101 286T105 299Q126 348 164 391T252 441Q253 441 260 441T272 442Q296 441 316 432Q341 418 354 401T367 348V332L318 133Q267 -67 264 -75Q246 -125 194 -164T75 -204Q25 -204 7 -183T-12 -137Q-12 -110 7 -91T53 -71Q70 -71 82 -81T95 -112Q95 -148 63 -167Q69 -168 77 -168Q111 -168 139 -140T182 -74L193 -32Q204 11 219 72T251 197T278 308T289 365Q289 372 288 376Z"></path><path stroke-width="1" id="E14-MJMATHI-6B" d="M121 647Q121 657 125 670T137 683Q138 683 209 688T282 694Q294 694 294 686Q294 679 244 477Q194 279 194 272Q213 282 223 291Q247 309 292 354T362 415Q402 442 438 442Q468 442 485 423T503 369Q503 344 496 327T477 302T456 291T438 288Q418 288 406 299T394 328Q394 353 410 369T442 390L458 393Q446 405 434 405H430Q398 402 367 380T294 316T228 255Q230 254 243 252T267 246T293 238T320 224T342 206T359 180T365 147Q365 130 360 106T354 66Q354 26 381 26Q429 26 459 145Q461 153 479 153H483Q499 153 499 144Q499 139 496 130Q455 -11 378 -11Q333 -11 305 15T277 90Q277 108 280 121T283 145Q283 167 269 183T234 206T200 217T182 220H180Q168 178 159 139T145 81T136 44T129 20T122 7T111 -2Q98 -11 83 -11Q66 -11 57 -1T48 16Q48 26 85 176T158 471L195 616Q196 629 188 632T149 637H144Q134 637 131 637T124 640T121 647Z"></path><path stroke-width="1" id="E14-MJMATHI-4E" d="M234 637Q231 637 226 637Q201 637 196 638T191 649Q191 676 202 682Q204 683 299 683Q376 683 387 683T401 677Q612 181 616 168L670 381Q723 592 723 606Q723 633 659 637Q635 637 635 648Q635 650 637 660Q641 676 643 679T653 683Q656 683 684 682T767 680Q817 680 843 681T873 682Q888 682 888 672Q888 650 880 642Q878 637 858 637Q787 633 769 597L620 7Q618 0 599 0Q585 0 582 2Q579 5 453 305L326 604L261 344Q196 88 196 79Q201 46 268 46H278Q284 41 284 38T282 19Q278 6 272 0H259Q228 2 151 2Q123 2 100 2T63 2T46 1Q31 1 31 10Q31 14 34 26T39 40Q41 46 62 46Q130 49 150 85Q154 91 221 362L289 634Q287 635 234 637Z"></path><path stroke-width="1" id="E14-MJMAIN-29" d="M60 749L64 750Q69 750 74 750H86L114 726Q208 641 251 514T294 250Q294 182 284 119T261 12T224 -76T186 -143T145 -194T113 -227T90 -246Q87 -249 86 -250H74Q66 -250 63 -250T58 -247T55 -238Q56 -237 66 -225Q221 -64 221 250T66 725Q56 737 55 738Q55 746 60 749Z"></path></defs><g stroke="currentColor" fill="currentColor" stroke-width="0" transform="matrix(1 0 0 -1 0 0)" style="--darkreader-inline-fill: currentColor; --darkreader-inline-stroke: currentColor;" data-darkreader-inline-fill="" data-darkreader-inline-stroke=""><use xlink:href="#E14-MJMAIN-28" x="0" y="0"></use><use xlink:href="#E14-MJMAIN-31" x="389" y="0"></use><use xlink:href="#E14-MJMAIN-2264" x="1167" y="0"></use><use xlink:href="#E14-MJMATHI-69" x="2224" y="0"></use><use xlink:href="#E14-MJMAIN-2C" x="2569" y="0"></use><use xlink:href="#E14-MJMATHI-6A" x="3014" y="0"></use><use xlink:href="#E14-MJMAIN-2C" x="3427" y="0"></use><use xlink:href="#E14-MJMATHI-6B" x="3872" y="0"></use><use xlink:href="#E14-MJMAIN-2264" x="4671" y="0"></use><use xlink:href="#E14-MJMATHI-4E" x="5727" y="0"></use><use xlink:href="#E14-MJMAIN-29" x="6616" y="0"></use></g></svg><span class="MJX_Assistive_MathML" role="presentation"><math xmlns="http://www.w3.org/1998/Math/MathML"><mo stretchy="false">(</mo><mn>1</mn><mo>≤</mo><mi>i</mi><mo>,</mo><mi>j</mi><mo>,</mo><mi>k</mi><mo>≤</mo><mi>N</mi><mo stretchy="false">)</mo></math></span></span><script type="math/tex" id="MathJax-Element-14">( 1 \leq i,j,k\leq N )</script></span>. You are also given a positive integer <em>S</em>.</p>

<p><strong>Task</strong></p>

<p>Determine the maximum value of <em>N</em> such that sum&nbsp;of all array elements doesn't exceed <em>S.</em></p>

<p><strong>Example</strong></p>

<p><em>Assumption</em></p>

<ul>
	<li><em>S = 90</em></li>
</ul>

<p><em>Approach</em></p>

<ul>
	<li>Let us check for <em>N = 1.</em><br>
	The only element of array <em>A</em>, <em>A[ 1 ][ 1 ][ 1 ]</em> equals 3. Hence, the sum of all array elements of <em>A</em> is 3, which doesn't exceed <em>S</em>.</li>
	<li>Now, for <em>N = 2.&nbsp;</em><br>
	Elements of A:&nbsp;<em>A[ 1 ][ 1 ][ 1 ] </em>= 3,&nbsp;<em>A[ 1 ][ 1 ][ 2&nbsp;]</em> = 8,&nbsp;<em>A[ 1 ][ 2&nbsp;][ 1 ]</em> = 4,&nbsp;<em>A[ 1 ][ 2&nbsp;][ 2&nbsp;] </em>= 10,&nbsp;<em>A[ 2&nbsp;][ 1 ][ 1 ] </em>= 8,&nbsp;<em>A[ 2 ][ 1 ][ 2&nbsp;]</em> = 20,&nbsp;<br>
	<em>A[ 2&nbsp;][ 2&nbsp;][ 1 ] </em>= 10,&nbsp;<em>A[ 2&nbsp;][ 2&nbsp;][ 2&nbsp;] </em>= 24. Sum of all elements equals 87,&nbsp;&nbsp;which again doesn't exceed <em>S.</em></li>
	<li>Similarly, if you calculate for <em>N = 3,</em>&nbsp;the sum of all elements comes out to be 720, which&nbsp;exceeds&nbsp;<em>S.</em></li>
	<li>Hence, the maximum value of <em>N</em> is 2.</li>
</ul>

<p><strong>Function description</strong></p>

<p>Complete the<em> Solve</em> function provided in the editor. This 
function takes the following a single parameter&nbsp;and returns an 
integer denoting the maximum value of <em>N:</em></p>

<ul>
	<li><em>S</em>: Represents a&nbsp;positive integer</li>
</ul>

<p><strong>Input format</strong></p>

<p><strong>Note</strong>: This is the input format that you must use to provide custom input (available above the&nbsp;<strong>Compile and Test&nbsp;</strong>button).</p>

<ul>
	<li>The first line contains an integer <em>T</em>&nbsp;denoting the number of test cases.&nbsp;<em>T&nbsp;</em>also specifies the number of times you have to run the <em>Solve&nbsp;</em>function on a different set of inputs.</li>
	<li>Next <em>T</em>&nbsp;lines follow:
	<ul>
		<li>Each line contains a single integer denoting the value of <em>S</em><em>.</em></li>
	</ul>
	</li>
</ul>

<p><strong>Output format</strong></p>

<p>For each test case, print a&nbsp;single integer in a new line denoting the maximum value of <em>N</em>.</p>

<p><strong>Constraints</strong><br>
<span class="mathjax-latex"><span class="MathJax_Preview" style="color: inherit; --darkreader-inline-color: inherit;" data-darkreader-inline-color=""></span><span style="font-size: 100%; display: inline-block; position: relative;" class="MathJax_SVG" id="MathJax-Element-15-Frame" tabindex="0" data-mathml="<math xmlns=&quot;http://www.w3.org/1998/Math/MathML&quot;><mn>1</mn><mo>&amp;#x2264;</mo><mi>T</mi><mo>&amp;#x2264;</mo><mn>5</mn><mo>&amp;#x00D7;</mo><msup><mn>10</mn><mn>5</mn></msup></math>" role="presentation"><span class="MJX_Assistive_MathML" role="presentation"><math xmlns="http://www.w3.org/1998/Math/MathML"><mn>1</mn><mo>≤</mo><mi>T</mi><mo>≤</mo><mn>5</mn><mo>×</mo><msup><mn>10</mn><mn>5</mn></msup></math></span></span><script type="math/tex" id="MathJax-Element-15">1\le T \le 5\times10^5</script></span><br>
<span class="mathjax-latex"><span class="MathJax_Preview" style="color: inherit; --darkreader-inline-color: inherit;" data-darkreader-inline-color=""></span><span style="font-size: 100%; display: inline-block; position: relative;" class="MathJax_SVG" id="MathJax-Element-16-Frame" tabindex="0" data-mathml="<math xmlns=&quot;http://www.w3.org/1998/Math/MathML&quot;><mn>3</mn><mo>&amp;#x2264;</mo><mi>S</mi><mo>&amp;#x2264;</mo><msup><mn>10</mn><mrow class=&quot;MJX-TeXAtom-ORD&quot;><mn>16</mn></mrow></msup></math>" role="presentation"><span class="MJX_Assistive_MathML" role="presentation"><math xmlns="http://www.w3.org/1998/Math/MathML"><mn>3</mn><mo>≤</mo><mi>S</mi><mo>≤</mo><msup><mn>10</mn><mrow class="MJX-TeXAtom-ORD"><mn>16</mn></mrow></msup></math></span></span><script type="math/tex" id="MathJax-Element-16">3\le S \le 10^{16}</script></span></p>

<p><strong>Code snippets (also called starter code/boilerplate code)</strong></p>

<p>This question has code snippets for C, CPP, Java, and Python.</p></div><div class="clear"></div>


<div class="view-sample-test-case d-flex margin-bottom-12"><div class="padding-right-36 w-50"><div class="d-flex title-container"><div class="sample-title">Sample input 1</div><span class="copy-text" role="presentation">Copy</span></div><div class="margin-top-12"><div class="sample-data"><div style="position: relative; height: 220px; width: 100%; overflow: auto; will-change: transform; direction: ltr;"><div style="height: 40px; width: 100%;"><pre style="position: absolute; left: 0px; top: 0px; height: 20px; width: 100%; padding-left: 16px; margin: 0px; white-space: pre; font-size: 12px;">1
</pre><pre style="position: absolute; left: 0px; top: 20px; height: 20px; width: 100%; padding-left: 16px; margin: 0px; white-space: pre; font-size: 12px;">720</pre></div></div></div></div></div><div class="w-50"><div class="d-flex title-container"><div class="sample-title">Sample output 1</div><span class="copy-text" role="presentation">Copy</span></div><div class="margin-top-12"><div class="sample-data"><div style="position: relative; height: 220px; width: 100%; overflow: auto; will-change: transform; direction: ltr;"><div style="height: 20px; width: 100%;"><pre style="position: absolute; left: 0px; top: 0px; height: 20px; width: 100%; padding-left: 16px; margin: 0px; white-space: pre; font-size: 12px;">3</pre></div></div></div></div></div></div><div class="margin-top-24"><div class="sample-title">Explanation</div><div class="explanation"><p><em>Given</em></p>

<ul>
	<li><em>T = 1</em>&nbsp;</li>
	<li><em>S = 720</em></li>
</ul>

<p><em>Approach</em></p>

<ul>
	<li>Let us check for <em>N = 1.</em><br>
	The only element of array <em>A</em>, <em>A[ 1 ][ 1 ][ 1 ]</em> equals 3. Hence the sum of all array elements of <em>A</em> is 1, which doesn't exceed <em>S</em>.</li>
	<li>Now, for <em>N = 2.&nbsp;</em><br>
	Elements of <em>A</em> :&nbsp;<em>A[ 1 ][ 1 ][ 1 ]</em> = 3,&nbsp;<em>A[ 1 ][ 1 ][ 2&nbsp;]</em> = 8,&nbsp;<em>A[ 1 ][ 2&nbsp;][ 1 ]</em> = 4,&nbsp;<em>A[ 1 ][ 2&nbsp;][ 2&nbsp;]</em> = 10,&nbsp;<em>A[ 2&nbsp;][ 1 ][ 1 ] </em>= 8,&nbsp;<em>A[ 2 ][ 1 ][ 2&nbsp;]</em> = 20,&nbsp;<br>
	<em>A[ 2&nbsp;][ 2&nbsp;][ 1 ]</em> = 10,&nbsp;<em>A[ 2&nbsp;][ 2&nbsp;][ 2&nbsp;]</em> = 24. Sum of all elements equals 87,&nbsp;&nbsp;which again doesn't exceed <em>S.</em></li>
	<li>Similarly, if you calculate for&nbsp;<em>N = 3,</em>&nbsp;the sum equals 720&nbsp;which doesn't exceed S. Nor bigger value of&nbsp;<em>N</em> is possible.</li>
	<li>Hence, the maximum value of <em>N</em> is 3.</li>
</ul></div></div><textarea class="text-area-to-copy"></textarea>

```