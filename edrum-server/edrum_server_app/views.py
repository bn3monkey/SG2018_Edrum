from rest_framework import viewsets
from rest_framework_filters import backends

from edrum_server_app.models import NoteFileModel
from edrum_server_app.serializers import NoteFileSerializer
#from edrum_server_app.filters import NoteFileFilter

class NoteFileViewSet(viewsets.ModelViewSet) :
    queryset = NoteFileModel.objects.all()
    serializer_class = NoteFileSerializer

    #filter_backends = (backends.DjangoFilterBackend,)
    #filter_class = NoteFileFilter

# Create your views here.

