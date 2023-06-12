[Top]
components : rmSource@rmSourceType productionBuffer@productionBufferType production@productionType 
out : rmCount finishedProduct totalFinishedProduct 
Link : out@rmSource in@productionBuffer
Link : out@productionBuffer in@production
Link : mg@productionBuffer mg@rmSource
Link : done@production done@productionBuffer
Link : rmCount@rmSource rmCount
Link : fpCount@production totalFinishedProduct
Link : out@production finishedProduct

[rmSource]
preparation : 00:00:00:000

[productionBuffer]
preparation : 00:00:01:000

[production]
preparation : 00:00:08:000


