from rest_framework import viewsets
from rest_framework_filters import backends
from rest_framework.response import Response

from edrum_server_app.models import NoteFileModel
from edrum_server_app.serializers import NoteFileSerializer
#from edrum_server_app.filters import NoteFileFilter
from edrum_server_app.pretty_request import pretty_request

class NoteFileViewSet(viewsets.ModelViewSet) :
    queryset = NoteFileModel.objects.all()
    serializer_class = NoteFileSerializer

    #filter_backends = (backends.DjangoFilterBackend,)
    #filter_class = NoteFileFilter

    #def create(self, request, pk = None):
        #f = open("Log2.txt", "w")
        #f.write(pretty_request(request))
        #f.close()
        #serializer = NoteFileSerializer(data=request.data)
        #if serializer.is_valid():
        #    serializer.Meta.model(request.data).save()
        #return Response()
# Create your views here.

